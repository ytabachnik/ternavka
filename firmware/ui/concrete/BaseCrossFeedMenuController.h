#ifndef CROSS_FEED_MENU_COMPONENT_H
#define CROSS_FEED_MENU_COMPONENT_H

#include "MenuController.h"
#include "SystemFacade.h"

#include "BaseUIModel.h"

// CrossFeed-project specific menu component.
class BaseCrossFeedMenuController : public MenuController
{
public:
    BaseCrossFeedMenuController(const std::string& name, BaseUIModel* model, BaseUIView* view,
        bool mainMenu);

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

    void onSelected() override
    {
        // Needed to show the name of the current mode.
        model->setSectionChanged((int)1);
    }

private:
    SystemFacade* facade;
};

#endif // CROSS_FEED_
