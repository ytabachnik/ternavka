#ifndef CROSS_FEED_MENU_COMPONENT_H
#define CROSS_FEED_MENU_COMPONENT_H

#include "MenuController.h"
#include "SystemFacade.h"

// CrossFeed-project specific menu component.
class BaseCrossFeedMenuController : public MenuController
{
public:
    BaseCrossFeedMenuController(const std::string& name, BaseUIModel* model, BaseUIView* view);

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

private:
    SystemFacade* facade;
};

#endif // CROSS_FEED_
