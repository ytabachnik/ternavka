cmake_minimum_required(VERSION 3.12)

project(ternavka C CXX ASM)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

pico_sdk_init()

add_executable(ternavka
    main.cpp
    lowlevel/MCP23S17.cpp
    lowlevel/TCA9548A.cpp

    hal/LEDManager.cpp
    hal/KeyboardManager.cpp
    hal/MultiDisplayManager.cpp

    configuration/Configuration.cpp 
    configuration/EncoderSettings.cpp 
    configuration/FeedSettings.cpp 
    configuration/StepMotorSettings.cpp 

    ui/BaseUIController.cpp 
    ui/BaseUIView.cpp 
    ui/MenuController.cpp 
    ui/DialogController.cpp 

    ui/concrete/BaseCrossFeedDialogController.cpp
    ui/concrete/BaseCrossFeedMenuController.cpp
    ui/concrete/FreeDialogController.cpp
#   ui/concrete/FreeDialogView.cpp

    SystemFacade.cpp
    CurrentTimeManager.cpp
)

add_subdirectory(libs/pico-ssd1306)

target_include_directories(ternavka PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
     hal
     lowlevel
     common
     configuration
     ui
     ui/concrete
     libs/pico-ssd1306
)

# pull in common dependencies
target_link_libraries(ternavka pico_stdlib pico_ssd1306 hardware_i2c hardware_spi hardware_flash)

# create map/bin/hex file etc.
pico_add_extra_outputs(ternavka)
