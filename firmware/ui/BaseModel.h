#ifndef BASE_MODEL_H
#define BASE_MODEL_H

class BaseController;

class BaseModel {
public:
    BaseModel(BaseController* controller) : controller(controller), changed(false) {}

    virtual bool isChanged() const {
        return changed;
    }

    void setChanged(bool changed) {
        this->changed = changed;
    }

protected:
    BaseController* controller;
    bool changed;
};

#endif // BASE_MODEL_H