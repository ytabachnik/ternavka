#ifndef DIALOG_VIEW_H
#define DIALOG_VIEW_H

#include <pico/stdlib.h>
#include <iostream>
#include "BaseUIView.h"

class DialogView : public BaseUIView
{
public:
    DialogView(BaseUIModel* model) : BaseUIView(model)
    {
    }
};

#endif // DIALOG_VIEW_H
