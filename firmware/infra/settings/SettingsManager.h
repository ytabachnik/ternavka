#ifndef _SETTINS_MANAGER_H_
#define _SETTINS_MANAGER_H_

#include <vector>
#include "SettingItem.h"

#include <vector>

class SettingsManager
{
private:
    std::vector<SettingsItemBase*> settingsItems;
    int activeIndex;

public:
    SettingsManager() : activeIndex(0) {}

    void addItem(SettingsItemBase* item)
    {
        settingsItems.push_back(item);
    }

    void switchToNextItem()
    {
        activeIndex = (activeIndex + 1) % settingsItems.size();
    }

    void switchToPrevItem()
    {
        activeIndex = (activeIndex - 1 + settingsItems.size()) % settingsItems.size();
    }

    SettingsItemBase* getActiveItem() const
    {
        return settingsItems[activeIndex];
    }
};

#endif //_SETTINS_MANAGER_H_

