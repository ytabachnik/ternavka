#ifndef BASE_CROSS_FEED_DIALOG_CONTROLLER_H
#define BASE_CROSS_FEED_DIALOG_CONTROLLER_H

#include "DialogController.h"
#include "SystemFacade.h"

class BaseCrossFeedDialogController : public DialogController
{
public:
    BaseCrossFeedDialogController(const std::string& name, BaseUIModel* model, BaseUIView* view);

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

private:
    SystemFacade* facade;
};

#endif // BASE_CROSS_FEED_DIALOG_CONTROLLER_H
