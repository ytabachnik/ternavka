#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
    virtual void handleButtonPress(int button) = 0;
};

#endif // CONTROLLER_H
