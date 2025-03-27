#include "BaseUIView.h"
#include "BaseUIModel.h"

void BaseUIView::update()
{
    if (model->isChanged())
    {
        render();
        model->setChanged(false);
    }
}
