#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include "Controller.h"
#include "View.h"
#include "Model.h"

#include "SystemFacade.h"

// MenuComponebt combines appropriate Controller, View and Model.
class MenuComponent {
private:
    Controller* controller;
    View* view;
    Model* model;
    SystemFacade* facade;

public:
    MenuComponent(Controller* controller, View* view, Model* model, SystemFacade* facade);
    Controller* getController() const;
    View* getView() const;
    Model* getModel() const;
    SystemFacade* getFacade() const;
};

#endif // MENUCOMPONENT_H
