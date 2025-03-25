#ifndef DIALOGCONTROLLER_H
#define DIALOGCONTROLLER_H

#include "Controller.h"
#include "DialogModel.h"
#include "DialogView.h"

class DialogController : public Controller {
private:
    DialogModel* model;
    DialogView* view;
public:
    DialogController(DialogModel* model, DialogView* view);
    void handleButtonPress(int button) override;
};

#endif // DIALOGCONTROLLER_H
