#ifndef _SETTING_ITEM_H_
#define _SETTING_ITEM_H_
 
#include <functional>

/// @brief Base class for all Setting Items.
class SettingsItemBase
{
public:
    virtual ~SettingsItemBase() = default;

    virtual void keyPressed(char key) {};
    virtual void display() const {};
};

/// @brief Template class for Setting Items.
/// @tparam T Type of the particular setting.
template <typename T> class SettingsItem : public SettingsItemBase
{
private:
    T value;
    std::function<T()> getValueFunc;
    std::function<void(T)> setValueFunc;

public:
    SettingsItem(T initialValue, std::function<T()> getValueFunc, std::function<void(T)> setValueFunc) 
        : value(initialValue), getValueFunc(getValueFunc), setValueFunc(setValueFunc)
    {
    }

    void keyPressed(char key)
    {
        // Modify value based on key pressed (example logic)
        if (key == '+') {
            value++;
        } else if (key == '-') {
            value--;
        }
        setValue(value);
    }

    T getValue() const
    {
        return value;
    }

    void setValue(T newValue)
    {
        value = newValue;
        setValue(value);
    }
};

#endif // _SETTING_ITEM_H_