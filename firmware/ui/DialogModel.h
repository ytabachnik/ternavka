#ifndef DIALOG_MODEL_H
#define DIALOG_MODEL_H

#include "BaseUIModel.h"

class DialogModel : public BaseUIModel
{
public:
    DialogModel() : BaseUIModel()
    {
        resetAllSections();
    }
};

#endif // DIALOG_MODEL_H
