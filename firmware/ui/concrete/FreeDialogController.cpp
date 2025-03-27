#include "FreeDialogController.h"
#include <iostream>

FreeDialogController::FreeDialogController(const std::string& name, BaseUIModel* model, BaseUIView* view) :
    BaseCrossFeedDialogController(name, model, view)
{
}

// Access to the proper model type.
FreeDialogModel* FreeDialogController::getModel()
{
    return static_cast<FreeDialogModel*>(model);
}

