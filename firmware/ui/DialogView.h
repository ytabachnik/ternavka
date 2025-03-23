#ifndef DIALOGVIEW_H
#define DIALOGVIEW_H

#include "View.h"
#include "DialogModel.h"

class DialogView : public View {
private:
    DialogModel* model;
public:
    DialogView(DialogModel* model);
    void render() override;
};

#endif // DIALOGVIEW_H