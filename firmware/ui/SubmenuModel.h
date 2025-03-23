#ifndef SUBMENUMODEL_H
#define SUBMENUMODEL_H

#include "Model.h"
#include "MenuComponent.h"
#include <string>
#include <vector>

class SubmenuModel : public Model {
private:
    std::string name;
    std::vector<MenuComponent*> items;
    int currentIndex;
    bool isActive;
public:
    SubmenuModel(const std::string& name);
    void addItem(MenuComponent* item);
    std::string getName() const;
    int getCurrentIndex() const;
    std::vector<MenuComponent*> getItems() const;
    void setCurrentIndex(int index);
    void setActive(bool active);
    bool getActive() const;
    void update() override;
};

#endif // SUBMENUMODEL_H