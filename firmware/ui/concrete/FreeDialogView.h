#ifndef FREE_DIALOG_VIEW_H
#define FREE_DIALOG_VIEW_H

#include "BaseCrossFeedDialogView.h"
#include "hal/MultiDisplayManager.h"

class FreeDialogView : public BaseCrossFeedDialogView
{
public:
    FreeDialogView(BaseUIModel* model) : BaseCrossFeedDialogView(model)
    {
    }

    void render(uint8_t sectionIndex) override
    {
        MultiDisplayManager* dm = getFacade()->getDisplayManager();

        SystemDisplayID displayID = static_cast<SystemDisplayID>(sectionIndex);
        switch (displayID)
        {
            case SystemDisplayID::LEFT_DISPLAY:
            {
                dm->setActiveDisplay(sectionIndex);
                dm->clear();

                EncoderMultiplier mult = getModel()->getEncoderMultiplier();
                if (mult == EncoderMultiplier::Off)
                {
                    dm->drawStringCentered(10, 2, "Off");
                }
                else if (mult == EncoderMultiplier::X1)
                {
                    dm->drawStringCentered(10, 2, "x1");
                }
                else if (mult == EncoderMultiplier::X10)
                {
                    dm->drawStringCentered(10, 2, "x10");
                }
                else if (mult == EncoderMultiplier::X100)
                {
                    dm->drawStringCentered(10, 2, "x100");
                }

                dm->show();
                break;
            }
        
            case SystemDisplayID::RIGHT_DISPLAY:
            {
                dm->setActiveDisplay(sectionIndex);
                dm->clear();

                char curPosStr[32] = {0};
                sprintf(curPosStr, "Position %i", getModel()->getPosition());
                dm->drawStringCentered(10, 1, curPosStr);

                dm->show();

                break;
            }

        default:
            break;
        }
    }

protected:
    // Access to the proper model type.
    FreeDialogModel* getModel()
    {
        return static_cast<FreeDialogModel*>(model);
    }
};

#endif // DIALOG_VIEW_H
