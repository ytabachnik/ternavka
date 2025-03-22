#include "MultiDisplayManager.h"

MultiDisplayManager::MultiDisplayManager(TCA9548A& tca, uint16_t width, uint16_t height,
    uint8_t address, i2c_inst_t* i2c_instance) : _tca(tca), _currentChannel(0)
{
    ssd1306_init(&_display, width, height, address, i2c_instance);
}

void MultiDisplayManager::setActiveDisplay(uint8_t channel)
{
    _tca.selectChannel(channel);
    _currentChannel = channel;
    ssd1306_init(&_display, _display.width, _display.height, _display.address, _display.i2c_i);
}

void MultiDisplayManager::deinit()
{
    ssd1306_deinit(&_display);
}

void MultiDisplayManager::powerOff()
{
    ssd1306_poweroff(&_display);
}

void MultiDisplayManager::powerOn()
{
    ssd1306_poweron(&_display);
}

void MultiDisplayManager::setContrast(uint8_t val)
{
    ssd1306_contrast(&_display, val);
}

void MultiDisplayManager::invertDisplay(uint8_t inv)
{
    ssd1306_invert(&_display, inv);
}

void MultiDisplayManager::show()
{
    ssd1306_show(&_display);
}

void MultiDisplayManager::clear()
{
    ssd1306_clear(&_display);
}

void MultiDisplayManager::clearPixel(uint32_t x, uint32_t y)
{
    ssd1306_clear_pixel(&_display, x, y);
}

void MultiDisplayManager::drawPixel(uint32_t x, uint32_t y)
{
    ssd1306_draw_pixel(&_display, x, y);
}

void MultiDisplayManager::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    ssd1306_draw_line(&_display, x1, y1, x2, y2);
}

void MultiDisplayManager::clearSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_clear_square(&_display, x, y, width, height);
}

void MultiDisplayManager::drawSquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_draw_square(&_display, x, y, width, height);
}

void MultiDisplayManager::drawEmptySquare(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    ssd1306_draw_empty_square(&_display, x, y, width, height);
}

void MultiDisplayManager::showImageWithOffset(const uint8_t* data, const long size, uint32_t x_offset, uint32_t y_offset) {
    ssd1306_bmp_show_image_with_offset(&_display, data, size, x_offset, y_offset);
}

void MultiDisplayManager::showImage(const uint8_t* data, const long size) {
    ssd1306_bmp_show_image(&_display, data, size);
}

void MultiDisplayManager::drawCharWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, char c) {
    ssd1306_draw_char_with_font(&_display, x, y, scale, font, c);
}

void MultiDisplayManager::drawChar(uint32_t x, uint32_t y, uint32_t scale, char c) {
    ssd1306_draw_char(&_display, x, y, scale, c);
}

void MultiDisplayManager::drawStringWithFont(uint32_t x, uint32_t y, uint32_t scale, const uint8_t* font, const char* s) {
    ssd1306_draw_string_with_font(&_display, x, y, scale, font, s);
}

void MultiDisplayManager::drawStringWithFontCentered(uint32_t y, uint32_t scale, const uint8_t* font, const char* s) {
    ssd1306_draw_string_with_font_centered(&_display, y, scale, font, s);
}

void MultiDisplayManager::drawString(uint32_t x, uint32_t y, uint32_t scale, const char* s) {
    ssd1306_draw_string(&_display, x, y, scale, s);
}

void MultiDisplayManager::drawStringCentered(uint32_t y, uint32_t scale, const char* s) {
    ssd1306_draw_string_centered(&_display, y, scale, s);
}
