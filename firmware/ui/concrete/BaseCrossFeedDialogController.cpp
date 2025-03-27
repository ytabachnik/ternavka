#include "BaseCrossFeedDialogController.h"
#include <iostream>

BaseCrossFeedDialogController::BaseCrossFeedDialogController(const std::string& name, BaseUIModel* model,
    BaseUIView* view) :
    DialogController(name, model, view),
    facade(nullptr)
{
}
