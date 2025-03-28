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

void FreeDialogController::handleKeyStateChanged(uint8_t keyIndex)
{
    BaseCrossFeedDialogController::handleKeyStateChanged(keyIndex);

    // Rights buttons are responsible for the actual position.
    // Left buttons are responsible for Encoder Multiplier.
    SystemKeyID keyID = static_cast<SystemKeyID>(keyIndex);
    switch (keyID)
    {
        case SystemKeyID::LEFT_UP_KEY: getModel()->setNextEncoderMultiplier(); break;
        case SystemKeyID::LEFT_DOWN_KEY: getModel()->setPrevEncoderMultiplier(); break;

        case SystemKeyID::RIGHT_UP_KEY: getModel()->increasePosition(); break;
        case SystemKeyID::RIGHT_DOWN_KEY: getModel()->decreasePosition(); break;

        default: break;
    }
}

