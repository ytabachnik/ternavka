#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"

#include "lowlevel/MCP23S17.h"
#include "lowlevel/TCA9548A.h"

#include "common/SystemConsts.h"

#include "hal/LEDManager.h"
#include "hal/KeyboardManager.h"
#include "hal/MultiDisplayManager.h"

#include "ui/MenuModel.h"
#include "ui/MenuView.h"
#include "ui/MenuController.h"
#include "ui/DialogModel.h"
#include "ui/DialogView.h"
#include "ui/DialogController.h"

#include "ui/concrete/FreeDialogModel.h"
#include "ui/concrete/FreeDialogView.h"
#include "ui/concrete/FreeDialogController.h"


#include "SystemFacade.h"
#include "CurrentTimeManager.h"

// SPI configuration.
// Constants for SPI pins
#define KYBD_SPI_PORT spi0
#define KYBD_SPI_SCK 18 // Physical pin 24
#define KYBD_SPI_MOSI_PIN 19 // Physical pin 25
#define KYBD_SPI_MISO_PIN 16 // Physical pin 21

#define KYBD_SPI_CS_PIN 5 // Physical pin 7

// An addr of the MCP23S17 controller, when A0, A1, A2 are set to 0.
#define KYBD_MCP23S17_ADDR 0x20

// I2C configuration.
#define DISPLAY_I2C_PORT i2c1
#define DISPLAY_I2C_SDA 2 // default SDA pin for I2C1, plysical pin 4
#define DISPLAY_I2C_SCL 3 // default SCL pin for I2C1, plysical pin 5

// Default addr of OLED display.
#define DISPLAY_DEFAULT_ADDR 0x3c

// Default address of TCA9548 extender
#define DISPLAY_EXTENDER_ADDR 0x70

const int LEDS_COUNT = 8;
const int KEYS_COUNT = 8;
const int DISPLAYS_COUNT = 3;

// Screens-specific info.
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

const int MAX_LED_STATE = 4;

struct LEDState
{
    int index;
    bool isChanged;
    bool keyHandled;
};

/// @brief Initialize the I2C part.
void initializeI2C()
{
    i2c_init(DISPLAY_I2C_PORT, 400 * 1000); // Initialize I2C at 400kHz
    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);
}

/// @brief Initialize the SPI part.
void initializeSPI()
{
    spi_init(KYBD_SPI_PORT, 1000 * 1000);  // 1 MHz
    gpio_set_function(KYBD_SPI_SCK, GPIO_FUNC_SPI);  // SCK
    gpio_set_function(KYBD_SPI_MOSI_PIN, GPIO_FUNC_SPI);  // MOSI
    gpio_set_function(KYBD_SPI_MISO_PIN, GPIO_FUNC_SPI);  // MISO

    gpio_init(KYBD_SPI_CS_PIN);
    gpio_set_dir(KYBD_SPI_CS_PIN, GPIO_OUT);
    gpio_put(KYBD_SPI_CS_PIN, 1);  // CS high
}

// Initialize the menu subsystem.
void initializeMenu(MenuController& rootLevelMenu, SystemFacade& facade);

MenuModel menuModel;
MenuView menuView(&menuModel);

DialogModel dialogModel;
DialogView dialogView(&dialogModel);

MenuController mainMenu("Main Menu", &menuModel, &menuView);

MenuController subMenu1("Sub Menu 1", &menuModel, &menuView);
MenuController subMenu2("Sub Menu 2", &menuModel, &menuView);
MenuController subSubMenu1("Sub Sub Menu 1", &menuModel, &menuView);
MenuController subSubMenu2("Sub Sub Menu 2", &menuModel, &menuView);

FreeDialogModel freeDialogModel;
FreeDialogView freeDialogView(&freeDialogModel);

FreeDialogController freeDialogController("FREE", &freeDialogModel, &freeDialogView);
DialogController dialog2("SubDialog 2", &dialogModel, &dialogView);

int main()
{
    stdio_init_all();

    initializeI2C();
    initializeSPI();

    // Low-level
    MCP23S17 mcp23s17(KYBD_SPI_CS_PIN, KYBD_SPI_PORT, KYBD_MCP23S17_ADDR);
    TCA9548A i2cExtender(DISPLAY_I2C_PORT, DISPLAY_EXTENDER_ADDR);

    // HAL.
    KeyboardManager kybdManager(mcp23s17, true, KEYS_COUNT);
    LEDManager ledManager(mcp23s17, false, LEDS_COUNT);

    MultiDisplayManager displayManager(i2cExtender, DISPLAYS_COUNT,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        DISPLAY_DEFAULT_ADDR, DISPLAY_I2C_PORT);

    // System Facade joins all the HAL components together.
    SystemFacade facade(&displayManager, &ledManager, &kybdManager);

    MenuController systemMenu("Main Menu", &menuModel, &menuView);
    initializeMenu(systemMenu, facade);

    /*
    displayManager.setActiveDisplay(0);
    displayManager.clear();
    displayManager.drawStringCentered(10, 1, "MAUUU");
    displayManager.show();

    displayManager.setActiveDisplay(1);
    displayManager.clear();
    displayManager.drawStringCentered(10, 2, "MRRR");
    displayManager.show();

    displayManager.setActiveDisplay(2);
    displayManager.clear();
    displayManager.drawStringCentered(10, 3, "MIII");
    displayManager.show();
    */

    while (true)
    {
        CurrentTimeManager::update();

        ledManager.update();

        for (uint8_t i = 0; i < (int8_t)KeyboardManager::KeyID::VALUE_COUNT; i ++)
        {
            KeyboardManager::KeyID keyID = static_cast<KeyboardManager::KeyID>(i);
            if (kybdManager.isKeyStateChanged(keyID))
            {
                systemMenu.handleKeyStateChanged(keyID);
            }
        }

        systemMenu.update();
    }

    return 0;
}

void initializeMenu(MenuController& systemMenu, SystemFacade& facade)
{
    freeDialogView.setFacade(&facade);
    freeDialogController.setFacade(&facade);
    mainMenu.add(&freeDialogController);

    mainMenu.add(&subMenu1);
    mainMenu.add(&subMenu2);

    subMenu1.add(&subSubMenu1);
    subMenu1.add(&subSubMenu2);
    subMenu1.add(&dialog2);

    mainMenu.setActive(&freeDialogController);
    systemMenu.setActive(&mainMenu);
}

/*
void initializeMenuSystem(MenuSystem& menuSystem, SystemFacade& facade)
{    
    // Create models
    // Settings - Screen
    DialogModel brightnessDialogModel("Brightness");
    DialogView brightnessDialogView(&brightnessDialogModel);
    DialogController brightnessDialogController(&brightnessDialogModel, &brightnessDialogView);
    BaseMenuComponent brightnessComponent(&brightnessDialogController, &brightnessDialogView, &brightnessDialogModel, &facade);

    DialogModel contrastDialogModel("Contrast");
    DialogView contrastDialogView(&contrastDialogModel);
    DialogController contrastDialogController(&contrastDialogModel, &contrastDialogView);
    BaseMenuComponent contrastComponent(&contrastDialogController, &contrastDialogView, &contrastDialogModel, &facade);

    // Settings - Connection
    DialogModel usbDialogModel("USB");
    DialogView usbDialogView(&usbDialogModel);
    DialogController usbDialogController(&usbDialogModel, &usbDialogView);
    BaseMenuComponent usbComponent(&usbDialogController, &usbDialogView, &usbDialogModel, &facade);

    DialogModel bluetoothDialogModel("Bluetooth");
    DialogView blueToothDialogView(&bluetoothDialogModel);
    DialogController blueToothDialogController(&bluetoothDialogModel, &blueToothDialogView);
    BaseMenuComponent blueToothComponent(&blueToothDialogController, &blueToothDialogView, &bluetoothDialogModel, &facade);

    DialogModel wifiDialogModel("wifi");
    DialogView wifiDialogView(&wifiDialogModel);
    DialogController wifiDialogController(&wifiDialogModel, &wifiDialogView);
    BaseMenuComponent wifiComponent(&wifiDialogController, &wifiDialogView, &wifiDialogModel, &facade);

    // Top level
    DialogModel freeDialogModel("FREE");
    DialogView freeDialogView(&freeDialogModel);
    DialogController freeDialogController(&freeDialogModel, &freeDialogView);
    BaseMenuComponent freeDialogComponent(&freeDialogController, &freeDialogView, &freeDialogModel, &facade);

    DialogModel stepDialogModel("STEP");
    DialogView stepDialogView(&stepDialogModel);
    DialogController stepDialogController(&stepDialogModel, &stepDialogView);
    BaseMenuComponent stepDialogComponent(&stepDialogController, &stepDialogView, &stepDialogModel, &facade);

    DialogModel settingsSubmenuModel("SETTINGS");
    DialogView settingsSubmenuView(&settingsSubmenuModel);
    DialogController settingsSubmenuController(&settingsSubmenuModel, &settingsSubmenuView);
    BaseMenuComponent settingsSubmenuComponent(&settingsSubmenuController, &settingsSubmenuView, &settingsSubmenuModel, &facade);

    DialogModel displaySubmenuModel("DISPLAY");
    DialogView displaySubmenuView(&displaySubmenuModel);
    DialogController displaySubmenuController(&displaySubmenuModel, &displaySubmenuView);
    SubmenuComponent displaySubmenuComponent(&displaySubmenuController, &displaySubmenuView, &displaySubmenuModel, &facade);

    DialogModel connectionSubmenuModel("connection");
    DialogView connectionSubmenuView(&connectionSubmenuModel);
    DialogController connectionSubmenuController(&connectionSubmenuModel, &connectionSubmenuView);
    SubmenuComponent connectionSubmenuComponent(&connectionSubmenuController, &connectionSubmenuView, &connectionSubmenuModel, &facade);

    // Build the hierarchy.
    DialogModel rootModel("root");
    DialogView rootView(&rootModel);
    DialogController rootController(&rootModel, &rootView);
    SubmenuComponent rootComponent(&rootController, &rootView, &rootModel, &facade);

    displaySubmenuComponent.addChildren(&brightnessComponent);
    displaySubmenuComponent.addChildren(&contrastComponent);

    connectionSubmenuComponent.addChildren(&usbComponent);
    connectionSubmenuComponent.addChildren(&wifiComponent);
    connectionSubmenuComponent.addChildren(&blueToothComponent);

    settingsSubmenuComponent.addChildren(&displaySubmenuComponent);
    settingsSubmenuComponent.addChildren(&connectionSubmenuComponent);

    rootComponent.addChildren(&freeDialogComponent);
    rootComponent.addChildren(&stepDialogComponent);
    rootComponent.addChildren(&settingsSubmenuComponent);
    rootComponent.setCurrentChildID(0);

    // Create menu system
    menuSystem.setRoot(&rootComponent);
}

*/