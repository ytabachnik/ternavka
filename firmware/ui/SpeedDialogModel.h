#ifndef SPEEDDIALOGMODEL_H
#define SPEEDDIALOGMODEL_H

#include "Model.h"
#include <string>

class SpeedDialogModel : public Model {
private:
    std::string name;
    int speed;
public:
    SpeedDialogModel(const std::string& name, int initialSpeed);
    void increaseSpeed();
    void decreaseSpeed();
    std::string getName() const;
    int getSpeed() const;
    void update() override;
};

#endif // SPEEDDIALOGMODEL_H
