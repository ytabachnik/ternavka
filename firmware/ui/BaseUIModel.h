#ifndef BASE_UI_MODEL_H
#define BASE_UI_MODEL_H

#include <pico/stdlib.h>
#include <iostream>

// Base UI Model for menus and dialogs.
class BaseUIModel
{
public:
    BaseUIModel()
    {
        resetAllSections();
    }

    // Section is a part of model which can be rendered separately (i.e. physical display).
    static const uint8_t MAX_UI_MODEL_SECTION = 8;

    // Method to set a section changed flag
    void setSectionChanged(uint8_t sectionIndex)
    {
        if (sectionIndex < MAX_UI_MODEL_SECTION)
        {
            changedSectionMask |= (1 << sectionIndex);
        }
    }

    // Method to check if a section changed flag is set
    bool isSectionChanged(uint8_t sectionIndex)
    {
        if (sectionIndex < MAX_UI_MODEL_SECTION)
        {
            return changedSectionMask & (1 << sectionIndex);
        }

        return false;
    }

    // Method to reset a section changed flag
    void resetSectionChanged(uint8_t sectionIndex)
    {
        if (sectionIndex < MAX_UI_MODEL_SECTION)
        {
            changedSectionMask &= ~(1 << sectionIndex);
        }
    }

    // Method to reset all section changed flags
    void resetAllSections()
    {
        changedSectionMask = 0;
    }

protected:
    // Bitwise field for the sections were changed.
    uint8_t changedSectionMask;
};

#endif // BASE_MODEL_H