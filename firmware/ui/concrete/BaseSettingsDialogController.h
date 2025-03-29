#ifndef BASE_SETTINS_DIALOG_CONTROLLER_H
#define BASE_SETTINS_DIALOG_CONTROLLER_H

#include "BaseCrossFeedDialogController.h"
#include "BaseSettingsDialogModel.h"

// Base dialog controller for "Settings"
class BaseSettingsDialogController : public BaseCrossFeedDialogController
{
public:
    BaseSettingsDialogController(const std::string& name, BaseUIModel* model, BaseUIView* view) :
        BaseCrossFeedDialogController(name, model, view)
    {
    }
    //void handleKeyStateChanged(KeyboardManager::KeyID keyID) override;
    //void handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress) override;

//  void onSelected() override;
//  void onDeselected() override;

protected:
    // Access to the proper model type.
    BaseSettingsDialogModel* getModel()
    {
        return static_cast<BaseSettingsDialogModel*>(model);
    }
};

#endif // FREE_DIALOG_CONTROLLER_H
