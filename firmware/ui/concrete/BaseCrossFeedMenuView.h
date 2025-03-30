#ifndef _BASE_CROSS_FEED_MENU_VIEW_H_
#define _BASE_CROSS_FEED_MENU_VIEW_H_

#include <iostream>
#include <string>

#include "MenuView.h"

#include "SystemConsts.h"
#include "SystemFacade.h"

class BaseCrossFeedMenuView : public MenuView
{
public:
    BaseCrossFeedMenuView(BaseUIModel* model, const std::string& baseViewName) :
    MenuView(model),
    facade(nullptr),
    viewName(baseViewName)
    {
    }

    void render(uint8_t sectionIndex) override
    {
        MultiDisplayManager* dm = getFacade()->getDisplayManager();

        SystemDisplayID displayID = static_cast<SystemDisplayID>(sectionIndex);

        switch (displayID)
        {
            case SystemDisplayID::CENTER_DISPLAY:
            {
                dm->setActiveDisplay(sectionIndex);
                dm->clear();

                dm->drawStringCentered(10, 2, viewName.c_str());

                dm->show();

                break;
            }
        }
    }

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

private:
    // System facade.
    SystemFacade* facade;

    // Base view name to render on the center screen.
    std::string viewName;
};

#endif // _BASE_CROSS_FEED_DIALOG_VIEW_H_
