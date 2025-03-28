#ifndef FREE_DIALOG_VIEW_H
#define FREE_DIALOG_VIEW_H

#include "BaseCrossFeedDialogView.h"
#include "FreeDialogModel.h"

// Dialog view for "Free" mode.
class FreeDialogView : public BaseCrossFeedDialogView
{
public:
    FreeDialogView(BaseUIModel* model);
    virtual ~FreeDialogView() = default;

    // Render the content of Free Dialog.
    void render(uint8_t sectionIndex) override;

protected:
    // Access to the proper model type.
    FreeDialogModel* getModel();
};

#endif // FREE_DIALOG_VIEW_H
