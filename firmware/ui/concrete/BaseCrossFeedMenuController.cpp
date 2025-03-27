#include "BaseCrossFeedMenuController.h"
#include <iostream>

#include "SystemConsts.h"

// CrossFeed-project specific menu component.
BaseCrossFeedMenuController::BaseCrossFeedMenuController(const std::string &name, BaseUIModel* model,
    BaseUIView* view) :
    MenuController(name, model, view),
    facade(nullptr)
{
}
