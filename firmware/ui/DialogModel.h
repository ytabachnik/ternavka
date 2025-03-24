#ifndef DIALOGMODEL_H
#define DIALOGMODEL_H

#include "Model.h"
#include <string>

enum DialogMode { MAIN, BLUE, GREEN };

class DialogModel : public Model {
private:
    DialogMode mode;
public:
    DialogModel(const std::string& name);

    void setMode(DialogMode newMode);
    DialogMode getMode() const;

    void update() override;
};

#endif // DIALOGMODEL_H