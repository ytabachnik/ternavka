#include <iostream>

#include "BaseCrossFeedMenuController.h"
#include "BaseUIModel.h"

#include "SystemConsts.h"

// CrossFeed-project specific menu component.
BaseCrossFeedMenuController::BaseCrossFeedMenuController(const std::string &name, BaseUIModel* model,
    BaseUIView* view, bool mainMenu) :
    MenuController(name, model, view, mainMenu),
    facade(nullptr)
{
}
