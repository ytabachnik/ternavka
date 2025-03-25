#ifndef _SUB_MENUCOMPONENT_H_
#define _SUB_MENUCOMPONENT_H_

#include "Controller.h"
#include "View.h"
#include "Model.h"

#include "SystemConsts.h"
#include "SystemFacade.h"

#include <pico/stdio.h>
#include <vector>

// SubMenuComponent is used to handle items with children.
class SubmenuComponent : public BaseMenuComponent
{
protected:
    BaseMenuComponent* nextLevelComponent;
    int8_t nextLevelComponentIndex;

public:
    SubmenuComponent(Controller* controller, View* view, Model* model, SystemFacade* facade) :
        BaseMenuComponent(controller, view, model, facade)
    {
        nextLevelComponent = nullptr;
    }

protected:
    // Handle the key state change (press) - base implementation. Returns TRUE if keypress is handled.
    virtual bool handleKeyStateChanged(int8_t keyIndex)
    {
        if (BaseMenuComponent::handleKeyStateChanged(keyIndex)) return true;

        // Fistly check whether a next level component is active.
        if (nextLevelComponent && nextLevelComponent->handleKeyStateChanged(keyIndex)) return true;

        // Submenu must have its children and be responsible for switching between them.
        SystemKeyID keyID = static_cast<SystemKeyID>(keyIndex);
        switch (keyID)
        {
            case SystemKeyID::MENU_PREV_KEY: return handlePrevKeyStateChanged();
            case SystemKeyID::MENU_NEXT_KEY: return handleNextKeyStateChanged();
            case SystemKeyID::MENU_OK_KEY: return handleOKKeyStateChanged();
        
        default:
            break;
        }

        //if (keyIndex == 6 && canDeactivateChild()) deactivateChild();

        // Wasn't handled on this level.
        return false;
    }
    
protected:
    // Called when Prev key state changed.
    virtual bool handlePrevKeyStateChanged()
    {
        // No way to select Prev/Next menu item if there is no children on this level.
        if (!hasChildren()) return false;

        if (canSelectPrev())
        {
            selectPrev();
            return true;
        }
        else
        {
            facade->getLEDManager()->errorBlink((int)SystemLedID::MENU_PREV_LED);
            return false;
        }
    }

    // Called when Next key state is changed.
    virtual bool handleNextKeyStateChanged()
    {
        // No way to select Prev/Next menu item if there is no children on this level.
        if (!hasChildren()) return false;
    
        if (canSelectNext())
        {
            selectNext();
            return true;
        }
        else
        {
            facade->getLEDManager()->errorBlink((int)SystemLedID::MENU_NEXT_LED);
            return false;
        }
    }
};

#endif // _SUB_MENUCOMPONENT_H_
