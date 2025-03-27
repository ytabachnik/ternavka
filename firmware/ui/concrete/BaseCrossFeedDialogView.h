#ifndef DIALOG_VIEW_H
#define DIALOG_VIEW_H

#include <iostream>
#include "BaseView.h"

class BaseCrossFeedDialogView : public DialogView
{
public:
    BaseCrossFeedDialogView(BaseUIModel* model) :
    BaseUIView(model),
    facade(nullptr)
    {
    }

    void render() override
    {
        // Implement rendering logic for the dialog view
        std::cout << "Rendering Dialog View" << std::endl;
    }

    // Access to the Facade.
    SystemFacade* getFacade() const {return facade;}
    void setFacade(SystemFacade* facade) {this->facade = facade;}

private:
    SystemFacade* facade;
};

#endif // DIALOG_VIEW_H
