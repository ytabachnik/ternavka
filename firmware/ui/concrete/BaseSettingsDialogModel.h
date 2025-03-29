#ifndef BASE_SETTINS_DIALOG_MODEL_H
#define BASE_SETTINS_DIALOG_MODEL_H

#include "DialogModel.h"
#include "infra/settings/SettingsManager.h"

// Base model for "Settings" dialog
class BaseSettingsDialogModel : public DialogModel
{
public:
    BaseSettingsDialogModel() : DialogModel()
    {
    }

protected:
    // Settings manager.
    SettingsManager settingsMgr;
};

#endif // BASE_SETTINS_DIALOG_MODEL_H
