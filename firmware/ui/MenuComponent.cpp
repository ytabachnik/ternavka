#include "MenuComponent.h"

MenuComponent::MenuComponent(Controller* controller, View* view, Model* model, SystemFacade* facade)
    : controller(controller),
      view(view),
      model(model),
      facade(facade)
{

}

Controller* MenuComponent::getController() const 
{
    return controller;
}

View* MenuComponent::getView() const 
{
    return view;
}

Model* MenuComponent::getModel() const 
{
    return model;
}

SystemFacade* MenuComponent::getFacade() const
{
    return facade;
}
