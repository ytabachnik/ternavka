#ifndef DIALOGMODEL_H
#define DIALOGMODEL_H

#include "Model.h"
#include <string>

enum DialogMode { MAIN, BLUE, GREEN };

class DialogModel : public Model {
private:
    std::string name;
    DialogMode mode;
public:
    DialogModel(const std::string& name);
    void setMode(DialogMode newMode);
    std::string getName() const;
    DialogMode getMode() const;
    void update() override;
};

#endif // DIALOGMODEL_H