#ifndef FREE_DIALOG_MODEL_H
#define FREE_DIALOG_MODEL_H

#include "DialogModel.h"

#include "common/SystemConsts.h"
#include "common/EncoderMultiplier.h"

// Model for "Free" dialog
class FreeDialogModel : public DialogModel
{
public:
    FreeDialogModel() : DialogModel()
    {
    }

    // Set the encoder multipliers.
    void setNextEncoderMultiplier()
    {
        if (encoderMultiplier != EncoderMultiplier::X100)
        {
            encoderMultiplier = static_cast<EncoderMultiplier>(static_cast<uint8_t>(encoderMultiplier) + 1);
            setSectionChanged((int)SystemDisplayID::LEFT_DISPLAY);
        }
    }

    void setPrevEncoderMultiplier()
    {
        if (encoderMultiplier != EncoderMultiplier::Off)
        {
            encoderMultiplier = static_cast<EncoderMultiplier>(static_cast<uint8_t>(encoderMultiplier) - 1);
            setSectionChanged((int)SystemDisplayID::LEFT_DISPLAY);
        }
    }

    EncoderMultiplier getEncoderMultiplier()
    {
        return encoderMultiplier;
    }

    // Increase/decrease position.
    void increasePosition() 
    {
        curPos += 10;
        setSectionChanged((int)SystemDisplayID::RIGHT_DISPLAY);
    }

    void decreasePosition()
    {
        curPos -= 10;
        setSectionChanged((int)SystemDisplayID::RIGHT_DISPLAY);
    }

    int32_t getPosition()
    {
        return curPos;
    }

protected:
    // Current position.
    int32_t curPos;

    // Encoder mode.
    EncoderMultiplier encoderMultiplier;
};

#endif // DIALOG_MODEL_H
