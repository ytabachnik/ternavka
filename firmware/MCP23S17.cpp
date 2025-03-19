#include "MCP23S17.h"
#include <stdio.h>

MCP23S17::MCP23S17(uint8_t cs_pin, spi_inst_t* spi_port, uint8_t address)
    : cs_pin(cs_pin), spi_port(spi_port), address(address) {
    init_spi();
}

void MCP23S17::init_spi() {
    spi_init(spi_port, 1000 * 1000);  // 1 MHz
    gpio_set_function(SCK_PIN, GPIO_FUNC_SPI);  // SCK
    gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);  // MOSI
    gpio_set_function(MISO_PIN, GPIO_FUNC_SPI);  // MISO
    gpio_init(cs_pin);
    gpio_set_dir(cs_pin, GPIO_OUT);
    gpio_put(cs_pin, 1);  // CS high
}

void MCP23S17::write_register(uint8_t reg, uint8_t value) {
    uint8_t data[3] = {0x40 | (address << 1), reg, value};  // Write command
    gpio_put(cs_pin, 0);  // CS low
    spi_write_blocking(spi_port, data, 3);
    gpio_put(cs_pin, 1);  // CS high
}

uint8_t MCP23S17::read_register(uint8_t reg) {
    uint8_t data[3] = {0x41 | (address << 1), reg, 0x00};  // Read command
    uint8_t rxdata[3];
    gpio_put(cs_pin, 0);  // CS low
    spi_write_read_blocking(spi_port, data, rxdata, 3);
    gpio_put(cs_pin, 1);  // CS high
    return rxdata[2];
}

void MCP23S17::enable_pullups_gpioa(bool enable) {
    write_register(GPPUA, enable ? 0xFF : 0x00);  // Enable pull-ups on all GPIOA pins
}

void MCP23S17::enable_pullups_gpiob(bool enable) {
    write_register(GPPUB, enable ? 0xFF : 0x00);  // Enable pull-ups on all GPIOB pins
}

uint8_t MCP23S17::read_gpioa() {
    return read_register(GPIOA);  // Read GPIOA register
}

uint8_t MCP23S17::read_gpiob() {
    return read_register(GPIOB);  // Read GPIOB register
}

void MCP23S17::write_pin_gpioa(uint8_t value) {
    write_register(GPIOA, value);
}

void MCP23S17::write_pin_gpiob(uint8_t value) {
    write_register(GPIOB, value);
}

void MCP23S17::set_pin_mode_gpioa(uint8_t mode) {
    write_register(IODIRA, mode);
}

void MCP23S17::set_pin_mode_gpiob(uint8_t mode) {
    write_register(IODIRB, mode);
}

void MCP23S17::set_pin_mode_gpioa(uint8_t gpio_reg, uint8_t pin, bool mode) {
    do_set_pin_mode(IODIRA, pin, mode);
}

void MCP23S17::set_pin_mode_gpiob(uint8_t gpio_reg, uint8_t pin, bool mode) {
    do_set_pin_mode(IODIRB, pin, mode);
}

void MCP23S17::write_pin_gpioa(uint8_t pin, bool value) {
    do_write_gpio_pin(GPIOA, pin, value);
}

void MCP23S17::write_pin_gpiob( uint8_t pin, bool value) {
    do_write_gpio_pin(GPIOB, pin, value);
}

void MCP23S17::do_set_pin_mode(uint8_t gpio_reg, uint8_t pin, bool mode) {
    uint8_t iodir_state = read_register(gpio_reg);
    
    if (mode == true) {
        iodir_state |= (1 << pin);
    } else {
        iodir_state &= ~(1 << pin);
    }
    
    write_register(gpio_reg, iodir_state);
}

void MCP23S17::do_write_gpio_pin(uint8_t gpio_reg, uint8_t pin, bool value) {
    uint8_t gpio_state = read_register(gpio_reg);
    
    if (value == true) {
        gpio_state |= (1 << pin);
    } else {
        gpio_state &= ~(1 << pin);
    }
    
    write_register(gpio_reg, gpio_state);
}
