#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model {
public:
    Model(const std::string& name)
    {
        this->name = name;
    }

    std::string getName() const
    {
        return name;
    }

    virtual void update() = 0;

protected:
    std::string name;
};

#endif // MODEL_H