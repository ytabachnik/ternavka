#include "SubmenuModel.h"

SubmenuModel::SubmenuModel(const std::string& name) : name(name), currentIndex(0), isActive(false) {}

void SubmenuModel::addItem(MenuComponent* item) {
    items.push_back(item);
}

std::string SubmenuModel::getName() const {
    return name;
}

int SubmenuModel::getCurrentIndex() const {
    return currentIndex;
}

std::vector<MenuComponent*> SubmenuModel::getItems() const {
    return items;
}

void SubmenuModel::setCurrentIndex(int index) {
    currentIndex = index;
    update();
}

void SubmenuModel::setActive(bool active) {
    isActive = active;
    update();
}

bool SubmenuModel::getActive() const {
    return isActive;
}

void SubmenuModel::update() {
    // Update logic for SubmenuModel
}