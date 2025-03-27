#ifndef BASE_UI_MODEL_H
#define BASE_UI_MODEL_H

// Base UI Model for menus and dialogs.
class BaseUIModel
{
public:
    BaseUIModel() : changed(false)
    {
    }

    virtual bool isChanged() const
    {
        return changed;
    }

    void setChanged(bool changed) 
    {
        this->changed = changed;
    }

protected:
    bool changed;
};

#endif // BASE_MODEL_H