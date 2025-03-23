#ifndef SYSTEMFACADE_H
#define SYSTEMFACADE_H

#include "MultiDisplayManager.h"
#include "LEDManager.h"
#include "KeyboardManager.h"

class SystemFacade {
private:
    MultiDisplayManager* displayManager;
    LEDManager* ledManager;
    KeyboardManager* keyboardManager;
public:
    SystemFacade(MultiDisplayManager* displayMgr, LEDManager* ledMgr, KeyboardManager* kybdMgr);

    // Getters for the underlying components
    MultiDisplayManager* getDisplayManager() const;
    LEDManager* getLEDManager() const;
    KeyboardManager* getKeyboardManager() const;
};

#endif //SYSTEMFACADE_H