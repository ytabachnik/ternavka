#ifndef MULTIDISPLAYMANAGER_H
#define MULTIDISPLAYMANAGER_H

#include "TCA9548A.h"

extern "C"
{
    #include "libs\pico-ssd1306\ssd1306.h"
}

class MultiDisplayManager {
public:
    MultiDisplayManager(TCA9548A& tca, uint16_t width, uint16_t height, uint8_t address, i2c_inst_t* i2c_instance);
    void setActiveDisplay(uint8_t channel);
    void deinit();
    void powerOff();
    void powerOn();
    void setContrast(uint8_t val);
    void invertDisplay(uint8_t inv);
    void show();
    void clear();
    void clearPixel(uint32_t x, uint32_t y);
    void drawPixel(uint32_t x, uint32_t y);
    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
    void clearSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawEmptySquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void showImageWithOffset(const uint8_t* data, const long size, uint32_t x_offset, uint32_t y_offset);
    void showImage(const uint8_t* data, const long size);
    void drawCharWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, char c);
    void drawChar(uint32_t x, uint32_t y, uint32_t scale, char c);
    void drawStringWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, const char* s);
    void drawStringWithFontCentered(uint32_t y, uint32_t scale, const uint8_t* font, const char* s);
    void drawString(uint32_t x, uint32_t y, uint32_t scale, const char* s);
    void drawStringCentered(uint32_t y, uint32_t scale, const char* s);

private:
    TCA9548A& _tca;
    ssd1306_t _display;
    uint8_t _currentChannel;
};

#endif
