#ifndef SUBMENUVIEW_H
#define SUBMENUVIEW_H

#include "View.h"
#include "SubmenuModel.h"

class SubmenuView : public View {
private:
    SubmenuModel* model;
public:
    SubmenuView(SubmenuModel* model);
    void render() override;
};

#endif // SUBMENUVIEW_H
