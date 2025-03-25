#ifndef SPEEDDIALOGVIEW_H
#define SPEEDDIALOGVIEW_H

#include "View.h"
#include "SpeedDialogModel.h"

class SpeedDialogView : public View {
private:
    SpeedDialogModel* model;
public:
    SpeedDialogView(SpeedDialogModel* model);
    void render() override;
};

#endif // SPEEDDIALOGVIEW_H