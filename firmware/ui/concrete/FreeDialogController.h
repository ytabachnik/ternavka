#ifndef FREE_DIALOG_CONTROLLER_H
#define FREE_DIALOG_CONTROLLER_H

#include "BaseCrossFeedDialogController.h"
#include "FreeDialogModel.h"

// Dialog controller for "Free" mode.
class FreeDialogController : public BaseCrossFeedDialogController
{
public:
    FreeDialogController(const std::string& name, BaseUIModel* model, BaseUIView* view);
    void handleKeyStateChanged(uint8_t keyIndex) override;

    void onSelected() override;
    void onDeselected() override;

protected:
    // Access to the proper model type.
    FreeDialogModel* getModel();
};

#endif // BASE_CROSS_FEED_DIALOG_COMPONENT_H
