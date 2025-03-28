#include "MenuController.h"
#include <iostream>

#include "SystemConsts.h"
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

void MenuController::addSubcontroller(BaseUIController* subController)
{
    subControllers.push_back(subController);
}

void MenuController::handleKeyStateChanged(uint8_t keyIndex)
{
    SystemKeyID keyID = static_cast<SystemKeyID>(keyIndex);
    if (activeSubcontroller && !activeSubcontroller->isTerminal())
    {
        activeSubcontroller->handleKeyStateChanged(keyIndex);
        if (keyID == SystemKeyID::MENU_CANCEL_KEY)
        {
            activeSubcontroller->onExited();
            activeSubcontroller = nullptr;
            onEntered(); // Re-enter the current menu
        }

        return;
    }

    // Send the key state changed flag to the active subcontroller, if any.
    if (activeSubcontroller)
    {
        activeSubcontroller->handleKeyStateChanged(keyIndex);
    }

    switch (keyID)
    {
        case SystemKeyID::MENU_PREV_KEY:
            if (!subControllers.empty()) 
            {
                if (selectedIndex == 0) 
                {
                    onAttemptToScrollBeforeFirstMenuItem();
                }
                else
                {
                    subControllers[selectedIndex]->onDeselected();
                    selectedIndex --;
                    subControllers[selectedIndex]->onSelected();

                    if (subControllers[selectedIndex]->isTerminal())
                    {
                        activeSubcontroller = subControllers[selectedIndex]; // Make the dialog active
                    }
                    else
                    {
                        activeSubcontroller = nullptr;
                    }
                }
            }

            break;

        case SystemKeyID::MENU_NEXT_KEY:
            if (!subControllers.empty()) 
            {
                if (selectedIndex == subControllers.size() - 1) 
                {
                    onAttemptToScrollAfterLastMenuItem();
                }
                else
                {
                    subControllers[selectedIndex]->onDeselected();
                    selectedIndex ++;
                    subControllers[selectedIndex]->onSelected();

                    if (subControllers[selectedIndex]->isTerminal())
                    {
                        activeSubcontroller = subControllers[selectedIndex]; // Make the dialog active
                    }
                    else
                    {
                        activeSubcontroller = nullptr;
                    }
                }
            }

            break;

        case SystemKeyID::MENU_OK_KEY:
            if (!subControllers.empty() && !subControllers[selectedIndex]->isTerminal())
            {
                subControllers[selectedIndex]->onEntered();
                activeSubcontroller = subControllers[selectedIndex];
            }
            break;

        case SystemKeyID::MENU_CANCEL_KEY:
            if (parent)
            {
                onExited();
                parent->activeSubcontroller = nullptr;
                parent->onEntered();  // Ensure parent menu is re-entered
            }
            break;

        default:
            break;
    }
}

void MenuController::display() {
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
