#ifndef SUBMENUCONTROLLER_H
#define SUBMENUCONTROLLER_H

#include "Controller.h"
#include "SubmenuModel.h"
#include "SubmenuView.h"

class SubmenuController : public Controller {
private:
    SubmenuModel* model;
    SubmenuView* view;
public:
    SubmenuController(SubmenuModel* model, SubmenuView* view);
    void handleButtonPress(int button) override;
};

#endif // SUBMENUCONTROLLER_H
