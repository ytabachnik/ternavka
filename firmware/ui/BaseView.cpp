#include "BaseView.h"
#include "BaseModel.h"

void BaseView::update()
{
    if (model->isChanged())
    {
        render();
        model->setChanged(false);
    }
}
