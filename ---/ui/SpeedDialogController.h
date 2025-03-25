#ifndef SPEEDDIALOGCONTROLLER_H
#define SPEEDDIALOGCONTROLLER_H

#include "Controller.h"
#include "SpeedDialogModel.h"
#include "SpeedDialogView.h"

class SpeedDialogController : public Controller {
private:
    SpeedDialogModel* model;
    SpeedDialogView* view;
public:
    SpeedDialogController(SpeedDialogModel* model, SpeedDialogView* view);
    void handleButtonPress(int button) override;
};

#endif // SPEEDDIALOGCONTROLLER_H
