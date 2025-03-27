#ifndef FREE_DIALOG_MODEL_H
#define FREE_DIALOG_MODEL_H

#include "DialogModel.h"

// Model for "Free" dialog
class FreeDialogModel : public DialogModel
{
public:
    FreeDialogModel() : DialogModel()
    {
    }

protected:
    // Speed in steps per second.
    int32_t stepsPerSecond;

    // Encoder mode.
    int8_t encoderMode;
};

#endif // DIALOG_MODEL_H
