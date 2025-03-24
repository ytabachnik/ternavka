#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include "Controller.h"
#include "View.h"
#include "Model.h"

#include "SystemFacade.h"

#include <pico/stdio.h>
#include <vector>

// MenuComponent combines appropriate Controller, View and Model.
class MenuComponent 
{
private:
    // Initial child IDs.
    const int8_t INITIAL_CURRENT_CHILD_ID = -1;
    const int8_t INITIAL_ACTIVE_CHILD_ID = -1;

    Controller* controller;
    View* view;
    Model* model;
    SystemFacade* facade;

    // Parent component.
    MenuComponent* parent;

    // List of children, if any.
    std::vector<MenuComponent*> children;

    // Current child.
    MenuComponent* curChild;
    int8_t curChildIndex;

    // Active child.
    MenuComponent* activeChild;
    int8_t activeChildIndex;

public:
    MenuComponent(Controller* controller, View* view, Model* model, SystemFacade* facade);

    Controller* getController() const;
    View* getView() const;
    Model* getModel() const;
    SystemFacade* getFacade() const;

    MenuComponent* getParent() const
    {
        return parent;
    }

    void setParent(MenuComponent* parent)
    {
        parent = parent;
    }

    // Handle the key state change (press) - base implementation. Returns TRUE if keypress is handled.
    virtual bool handleKeyStateChanged(int8_t keyIndex)
    {
        // Firstly send the key presses to the active child, if any.
        if (activeChild && activeChild->handleKeyStateChanged(keyIndex)) return true;
        
        // Then - to the current child, if any.
        if (curChild && curChild->handleKeyStateChanged(keyIndex)) return true;

        // TODO: now call the method on the particular class level.
        //if (keyIndex == 5 && canActivateChild()) activateChild();
        // TEMP!!!
        if (keyIndex == 1 && canSelectPrev())
        {
            selectPrev();
            return true;
        }

        if (keyIndex == 2 && canSelectNext())
        {
            selectNext();
            return true;
        }

        //if (keyIndex == 6 && canDeactivateChild()) deactivateChild();

        // Wasn't handled on this level.
        return false;
    }
    
    // Add the children on this level.
    void addChildren(MenuComponent* child)
    {
        children.push_back(child);
    }

    // Set the current children.
    void setCurrentChildID(int8_t index)
    {
        if (index >= 0 && index < children.size())
        {
            if (curChild) curChild->deactivate();

            curChildIndex = index;
            curChild = children[curChildIndex];

            curChild->activate();
        }
    }

    // Whether the current component has children?
    bool hasChildren()
    {
        return children.size() > 0;
    }

    // Can the next item be selected?
    bool canSelectNext()
    {
        if (!hasChildren()) return false;
        if (curChildIndex >= children.size() - 1) return false;

        return true;
    }

    // Can the prev item be selected?
    bool canSelectPrev()
    {
        if (!hasChildren()) return false;
        if (curChildIndex <= 0) return false;

        return true;
    }

    // Select next.
    void selectNext()
    {
        if (!canSelectNext())
        {
            return;
        }

        // Selecting the next children.
        curChild->deactivate();

        curChildIndex ++;
        curChild = children[curChildIndex];

        curChild->activate();
    }

    // Select prev.
    void selectPrev()
    {
        if (!canSelectPrev())
        {
            return;
        }

        // Selecting the prev children.
        curChild->deactivate();

        curChildIndex --;
        curChild = children[curChildIndex];

        curChild->activate();
    }

    // Activate the child item (one level down).
    void activateChild()
    {
        if (!hasChildren()) return;

        // Storing current child as active one.
        activeChild = curChild;
        activeChildIndex = curChildIndex;
    }

    // Deactivate the child item (one level up).
    void deactivateChild()
    {
        if (!hasChildren() || !activeChild) return;

        activeChild = nullptr;
        activeChildIndex = INITIAL_ACTIVE_CHILD_ID;
    }

    // Can we activate the child (go one level down)?
    bool canActivateChild()
    {
        if (!hasChildren()) return false;
        if (activeChild)
        {
             // This one can have its own children.
             return activeChild->canActivateChild();
        }

        // We have kids and no one was activated. For sure we can activate current one.
        return true;
    }

    // Can we deactivate the child (go one level up)?
    bool canDeactivateChild()
    {
        if (!hasChildren()) return false;
        if (activeChild)
        {
             // This one can have its own children.
             return activeChild->canDeactivateChild();
        }

        // We have kids and no one was activated - nothing to deactivate.
        return false;
    }

    void update()
    {
    }

protected:
    // Called by a menu system when a component is activated.
    virtual void activate() 
    {
        printf("Component %s is ACTIVATED\n", model->getName().c_str());
    }

    // Called by a menu system when a component is deactivated.
    virtual void deactivate()
    {
        printf("Component %s is DEACTIVATED\n", model->getName().c_str());
    }
};

#endif // MENUCOMPONENT_H
