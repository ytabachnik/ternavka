#include "BaseUIView.h"
#include "BaseUIModel.h"

void BaseUIView::update()
{
    for (uint8_t i = 0; i < BaseUIModel::MAX_UI_MODEL_SECTION; i ++)
    {
        if (model->isSectionChanged(i))
        {
            render(i);
        }
    }

    model->resetAllSections();
}
