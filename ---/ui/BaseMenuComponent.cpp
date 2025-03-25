#include "BaseMenuComponent.h"

BaseMenuComponent::BaseMenuComponent(Controller* controller, View* view, Model* model, SystemFacade* facade)
    : controller(controller),
      view(view),
      model(model),
      facade(facade),

      curChild(nullptr),
      curChildIndex(-1),
      activeChild(nullptr),
      activeChildIndex(-1)
{
}

Controller* BaseMenuComponent::getController() const 
{
    return controller;
}

View* BaseMenuComponent::getView() const 
{
    return view;
}

Model* BaseMenuComponent::getModel() const 
{
    return model;
}

SystemFacade* BaseMenuComponent::getFacade() const
{
    return facade;
}
