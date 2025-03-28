#include "MultiDisplayManager.h"
#include "ssd1306.h"

MultiDisplayManager::MultiDisplayManager(TCA9548A& tca, uint8_t count, uint16_t width,
     uint16_t height, uint8_t address, i2c_inst_t* i2c_instance)
    : _tca(tca), _channelsCount(count), _currentChannel(0)
{
    for (int i = 0; i < _channelsCount; ++i)
    {
        _displays[i].external_vcc = false; // or the display will show nothing.
        ssd1306_init(&_displays[i], width, height, address, i2c_instance);
    }
}

void MultiDisplayManager::setActiveDisplay(uint8_t channel) 
{
    if (channel >= _channelsCount) return;
    _tca.selectChannel(channel);
    _currentChannel = channel;

    // YT, 2025/03/23: commented out to avoid extra flickering.
    //ssd1306_init(&_displays[channel], _displays[channel].width, _displays[channel].height, _displays[channel].address, _displays[channel].i2c_i);
}

void MultiDisplayManager::deinit() {
    ssd1306_deinit(&_displays[_currentChannel]);
}

void MultiDisplayManager::powerOff() {
    ssd1306_poweroff(&_displays[_currentChannel]);
}

void MultiDisplayManager::powerOn() {
    ssd1306_poweron(&_displays[_currentChannel]);
}

void MultiDisplayManager::setContrast(uint8_t val) {
    ssd1306_contrast(&_displays[_currentChannel], val);
}

void MultiDisplayManager::invertDisplay(uint8_t inv) {
    ssd1306_invert(&_displays[_currentChannel], inv);
}

void MultiDisplayManager::show() {
    ssd1306_show(&_displays[_currentChannel]);
}

void MultiDisplayManager::clear() {
    ssd1306_clear(&_displays[_currentChannel]);
}

void MultiDisplayManager::clearPixel(uint32_t x, uint32_t y) {
    ssd1306_clear_pixel(&_displays[_currentChannel], x, y);
}

void MultiDisplayManager::drawPixel(uint32_t x, uint32_t y) {
    ssd1306_draw_pixel(&_displays[_currentChannel], x, y);
}

void MultiDisplayManager::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    ssd1306_draw_line(&_displays[_currentChannel], x1, y1, x2, y2);
}

void MultiDisplayManager::clearSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_clear_square(&_displays[_currentChannel], x, y, width, height);
}

void MultiDisplayManager::drawSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_draw_square(&_displays[_currentChannel], x, y, width, height);
}

void MultiDisplayManager::drawEmptySquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_draw_empty_square(&_displays[_currentChannel], x, y, width, height);
}

void MultiDisplayManager::showImageWithOffset(const uint8_t* data, const long size, uint32_t x_offset, uint32_t y_offset) {
    ssd1306_bmp_show_image_with_offset(&_displays[_currentChannel], data, size, x_offset, y_offset);
}

void MultiDisplayManager::showImage(const uint8_t* data, const long size) {
    ssd1306_bmp_show_image(&_displays[_currentChannel], data, size);
}

void MultiDisplayManager::drawCharWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, char c) {
    ssd1306_draw_char_with_font(&_displays[_currentChannel], x, y, scale, font, c);
}

void MultiDisplayManager::drawChar(uint32_t x, uint32_t y, uint32_t scale, char c) {
    ssd1306_draw_char(&_displays[_currentChannel], x, y, scale, c);
}

void MultiDisplayManager::drawStringWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, const char* s) {
    ssd1306_draw_string_with_font(&_displays[_currentChannel], x, y, scale, font, s);
}

void MultiDisplayManager::drawStringWithFontCentered(uint32_t y, uint32_t scale, const uint8_t* font, const char* s) {
    ssd1306_draw_string_with_font_centered(&_displays[_currentChannel], y, scale, font, s);
}

void MultiDisplayManager::drawString(uint32_t x, uint32_t y, uint32_t scale, const char* s) {
    ssd1306_draw_string(&_displays[_currentChannel], x, y, scale, s);
}

void MultiDisplayManager::drawStringCentered(uint32_t y, uint32_t scale, const char* s) {
    ssd1306_draw_string_centered(&_displays[_currentChannel], y, scale, s);
}
