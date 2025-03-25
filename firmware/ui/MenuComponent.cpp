#include "MenuComponent.h"
#include <iostream>

#include "SystemConsts.h"

MenuComponent::MenuComponent(const std::string& name) :
    BaseMenuComponent(name),
    parent(nullptr), activeSubMenu(nullptr), selectedIndex(0)
{
}

// Menu Components are NEVER Terminal.
bool MenuComponent::isTerminal() const
{
    return false;
}

void MenuComponent::addSubMenu(BaseMenuComponent* subMenu) 
{
    subMenus.push_back(subMenu);
}

void MenuComponent::handleKeyStateChanged(int8_t keyIndex)
{
    SystemKeyID keyID = static_cast<SystemKeyID>(keyIndex);
    if (activeSubMenu && !activeSubMenu->isTerminal())
    {
        activeSubMenu->handleKeyStateChanged(keyIndex);
        if (keyID == SystemKeyID::MENU_CANCEL_KEY)
        {
            activeSubMenu->onExited();
            activeSubMenu = nullptr;
            onEntered(); // Re-enter the current menu
        }

        return;
    }

    switch (keyID)
    {    
        case SystemKeyID::MENU_PREV_KEY:
            if (!subMenus.empty()) 
            {
                if (selectedIndex == 0) 
                {
                    onAttemptToScrollBeforeFirstMenuItem();
                }
                else
                {
                    subMenus[selectedIndex]->onDeselected();
                    selectedIndex --;
                    subMenus[selectedIndex]->onSelected();

                    if (subMenus[selectedIndex]->isTerminal())
                    {
                        activeSubMenu = subMenus[selectedIndex]; // Make the dialog active
                    }
                    else
                    {
                        activeSubMenu = nullptr;
                    }
                }
            }

            break;

        case SystemKeyID::MENU_NEXT_KEY:
            if (!subMenus.empty()) 
            {
                if (selectedIndex == subMenus.size() - 1) 
                {
                    onAttemptToScrollAfterLastMenuItem();
                }
                else
                {
                    subMenus[selectedIndex]->onDeselected();
                    selectedIndex ++;
                    subMenus[selectedIndex]->onSelected();

                    if (subMenus[selectedIndex]->isTerminal())
                    {
                        activeSubMenu = subMenus[selectedIndex]; // Make the dialog active
                    }
                    else
                    {
                        activeSubMenu = nullptr;
                    }
                }
            }

            break;

        case SystemKeyID::MENU_OK_KEY:
            if (!subMenus.empty() && !subMenus[selectedIndex]->isTerminal())
            {
                subMenus[selectedIndex]->onEntered();
                activeSubMenu = subMenus[selectedIndex];
            }
            break;

        case SystemKeyID::MENU_CANCEL_KEY:
            if (parent)
            {
                onExited();
                parent->activeSubMenu = nullptr;
                parent->onEntered();  // Ensure parent menu is re-entered
            }
            break;

        default:
            break;
    }
}

void MenuComponent::display() {
    std::cout << "Menu: " << name << std::endl;
    if (activeSubMenu) {
        activeSubMenu->display();
    } else {
        for (size_t i = 0; i < subMenus.size(); ++i) {
            if (i == selectedIndex) {
                std::cout << "> " << subMenus[i]->getName() << std::endl;
            } else {
                std::cout << "  " << subMenus[i]->getName() << std::endl;
            }
        }
    }
}

// New methods implementations
void MenuComponent::onEntered()
{
    std::cout << name << " entered." << std::endl;
}

void MenuComponent::onExited()
{
    std::cout << name << " exited." << std::endl;
}

void MenuComponent::onSelected()
{
    std::cout << name << " selected." << std::endl;
}

void MenuComponent::onDeselected()
{
    std::cout << name << " deselected." << std::endl;
}

void MenuComponent::onAttemptToScrollBeforeFirstMenuItem()
{
    std::cout << name << " SCROLL TOO LEFT." << std::endl;
}

void MenuComponent::onAttemptToScrollAfterLastMenuItem()
{
    std::cout << name << " SCROLL TOO RIGHT." << std::endl;
}
