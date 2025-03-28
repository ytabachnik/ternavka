#ifndef _BASE_CROSS_FEED_DIALOG_VIEW_H_
#define _BASE_CROSS_FEED_DIALOG_VIEW_H_

#include <iostream>
#include "DialogView.h"
#include "SystemFacade.h"

class BaseCrossFeedDialogView : public DialogView
{
public:
    BaseCrossFeedDialogView(BaseUIModel* model) :
    DialogView(model),
    facade(nullptr)
    {
    }

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

private:
    SystemFacade* facade;
};

#endif // _BASE_CROSS_FEED_DIALOG_VIEW_H_
