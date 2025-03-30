#include "FreeDialogController.h"
#include <iostream>

#include "common/SystemConsts.h"

FreeDialogController::FreeDialogController(const std::string& name, BaseUIModel* model, BaseUIView* view) :
    BaseCrossFeedDialogController(name, model, view)
{
}

// Access to the proper model type.
FreeDialogModel* FreeDialogController::getModel()
{
    return static_cast<FreeDialogModel*>(model);
}

void FreeDialogController::onSelected()
{
    // Needed to show the name of the current mode.
    getModel()->setSectionChanged((int)SystemDisplayID::CENTER_DISPLAY);
}

void FreeDialogController::onDeselected()
{
}

bool FreeDialogController::handleKeyStateChanged(KeyboardManager::KeyID keyID)
{
    BaseCrossFeedDialogController::handleKeyStateChanged(keyID);

    // Left buttons are responsible for Encoder Multiplier.
    switch (keyID)
    {
        case KeyboardManager::KeyID::Key0: getModel()->setNextEncoderMultiplier(); break;
        case KeyboardManager::KeyID::Key7: getModel()->setPrevEncoderMultiplier(); break;

        default: break;
    }

    return false;
}

void FreeDialogController::handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress)
{
    // Right buttons are responsible for the actual position.
    // Temp code to do not increase the speed way too often.
    if (timeSincePress % 1000 > 500)
    {
        switch (keyID)
        {
            case KeyboardManager::KeyID::Key3: getModel()->increasePosition(); break;
            case KeyboardManager::KeyID::Key4: getModel()->decreasePosition(); break;

            default: break;
        }
    }
}
