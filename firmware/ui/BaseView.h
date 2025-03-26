#ifndef BASE_VIEW_H
#define BASE_VIEW_H

class BaseModel;
class BaseController;

class BaseView {
public:
    BaseView(BaseModel* model, BaseController* controller)
        : model(model), controller(controller) {}

    virtual void update();

    virtual void render() = 0;

protected:
    BaseModel* model;
    BaseController* controller;
};

#endif // BASE_VIEW_H
