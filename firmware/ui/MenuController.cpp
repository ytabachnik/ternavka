#include "MenuController.h"
#include <iostream>

#include "KeyboardManager.h"

MenuController::MenuController(const std::string& name, BaseUIModel* model, BaseUIView* view) :
    BaseUIController(name, model, view), parent(nullptr),
    activeSubcontroller(nullptr), selectedIndex(0)
{
}

// Menu Components are NEVER Terminal.
bool MenuController::isTerminal() const
{
    return false;
}

void MenuController::add(BaseUIController* subController)
{
    subControllers.push_back(subController);
}

void MenuController::setActive(BaseUIController* subController)
{
    if (activeSubcontroller)
    {
        activeSubcontroller->onDeselected();
    }

    activeSubcontroller = subController;

    if (activeSubcontroller)
    {
        activeSubcontroller->onSelected();
    }
}

void MenuController::handleKeyStateChanged(KeyboardManager::KeyID keyID)
{
    if (activeSubcontroller && !activeSubcontroller->isTerminal())
    {
        activeSubcontroller->handleKeyStateChanged(keyID);
        if (keyID == KeyboardManager::KeyID::Key6)
        {
            activeSubcontroller->onExited();
            activeSubcontroller = nullptr;
            onEntered(); // Re-enter the current menu
        }

        return;
    }
    else if (activeSubcontroller && activeSubcontroller->isTerminal())
    {
        // Send the key state changed flag to the active subcontroller, if any.
        activeSubcontroller->handleKeyStateChanged(keyID);
    }

    switch (keyID)
    {
        case KeyboardManager::KeyID::Key1:
        {
            prevKeyStateChanged();
            break;
        }

        case KeyboardManager::KeyID::Key2:
        {
            nextKeyStateChanged();
            break;
        }

        case KeyboardManager::KeyID::Key5:
        {
            OKKeyStateChanged();
            break;
        }

        case KeyboardManager::KeyID::Key6:
        {
            cancelKeyStateChanged();
            break;
        }

        default:
            break;
    }
}

void MenuController::handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress)
{
    // Menu Controller does not perform any handling for pressed (and hold) key for now.
    if (activeSubcontroller)
    {
        activeSubcontroller->handleKeyPressed(keyID, timeSincePress);
    }
}

void MenuController::display()
{
    std::cout << "Menu: " << name << std::endl;
    if (activeSubcontroller)
    {
        activeSubcontroller->display();
    } else {
        for (size_t i = 0; i < subControllers.size(); ++i) {
            if (i == selectedIndex) {
                std::cout << "> " << subControllers[i]->getName() << std::endl;
            } else {
                std::cout << "  " << subControllers[i]->getName() << std::endl;
            }
        }
    }
}

// "Prev" key state is changed.
bool MenuController::prevKeyStateChanged()
{
    if (subControllers.empty()) return false;

    if (selectedIndex == 0)
    {
        // No way to continue scrolling left.
        onAttemptToScrollBeforeFirstMenuItem();
        return false;
    }

    subControllers[selectedIndex]->onDeselected();
    selectedIndex --;
    subControllers[selectedIndex]->onSelected();

    selectActiveSubcontrollerIfTerminal();
    return true;
}

// "Next" key state is changed.
bool MenuController::nextKeyStateChanged()
{
    if (subControllers.empty()) return false;

    if (selectedIndex == subControllers.size() - 1)
    {
        onAttemptToScrollAfterLastMenuItem();
        return false;
    }

    subControllers[selectedIndex]->onDeselected();
    selectedIndex++;
    subControllers[selectedIndex]->onSelected();

    selectActiveSubcontrollerIfTerminal();
    return true;
}

bool MenuController::OKKeyStateChanged()
{
    if (!subControllers.empty() && !subControllers[selectedIndex]->isTerminal())
    {
        subControllers[selectedIndex]->onEntered();
        activeSubcontroller = subControllers[selectedIndex];
        return true;
    }

    return false;
}

bool MenuController::cancelKeyStateChanged()
{
    if (parent)
    {
        onExited();
        parent->activeSubcontroller = nullptr;
        parent->onEntered(); // Ensure parent menu is re-entered

        return true;
    }

    return false;
}

/// @brief Select the subcontroller as active, if it is terminal (dialog)
void MenuController::selectActiveSubcontrollerIfTerminal()
{
    if (subControllers[selectedIndex]->isTerminal())
    {
        activeSubcontroller = subControllers[selectedIndex]; // Make the dialog active
    }
    else
    {
        activeSubcontroller = nullptr;
    }
}

// Override virtual methods
void MenuController::onEntered()
{
    std::cout << name << " entered." << std::endl;
}

void MenuController::onExited()
{
    std::cout << name << " exited." << std::endl;
}

void MenuController::onSelected()
{
    std::cout << name << " selected." << std::endl;
}

void MenuController::onDeselected()
{
    std::cout << name << " deselected." << std::endl;
}

void MenuController::onAttemptToScrollBeforeFirstMenuItem()
{
    std::cout << name << " SCROLL TOO LEFT." << std::endl;
}

void MenuController::onAttemptToScrollAfterLastMenuItem()
{
    std::cout << name << " SCROLL TOO RIGHT." << std::endl;
}
