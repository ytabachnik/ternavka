#include "SystemFacade.h"

SystemFacade::SystemFacade(MultiDisplayManager* displayMgr, LEDManager* ledMgr, KeyboardManager* kybdMgr)
    : displayManager(displayMgr),
      ledManager(ledMgr),
      keyboardManager(kybdMgr)
{
}

// Getters for the underlying components
MultiDisplayManager* SystemFacade::getDisplayManager() const
{
    return displayManager;
}

LEDManager* SystemFacade::getLEDManager() const
{
    return ledManager;
}

KeyboardManager* SystemFacade::getKeyboardManager() const
{
    return keyboardManager;
}