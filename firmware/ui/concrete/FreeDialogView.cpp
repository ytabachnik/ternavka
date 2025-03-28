#include "FreeDialogView.h"

#include "common/SystemConsts.h"
#include "common/EncoderMultiplier.h"

#include "hal/MultiDisplayManager.h"

FreeDialogView::FreeDialogView(BaseUIModel* model) : BaseCrossFeedDialogView(model)
{
}

void FreeDialogView::render(uint8_t sectionIndex)
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

        case SystemDisplayID::CENTER_DISPLAY:
        {
            dm->setActiveDisplay(sectionIndex);
            dm->clear();

            dm->drawStringCentered(10, 2, "FREE MODE");

            dm->show();

            break;
        }

        case SystemDisplayID::RIGHT_DISPLAY:
        {
            dm->setActiveDisplay(sectionIndex);
            dm->clear();

            char curPosStr[32] = {0};
            sprintf(curPosStr, "Position %i", getModel()->getPosition());
            dm->drawStringCentered(10, 2, curPosStr);

            dm->show();

            break;
        }

        default:
            break;
    }
}

// Access to the proper model type.
FreeDialogModel* FreeDialogView::getModel()
{
    return static_cast<FreeDialogModel*>(model);
}
