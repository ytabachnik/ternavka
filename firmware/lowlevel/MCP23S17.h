#ifndef MCP23S17_H
#define MCP23S17_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

class MCP23S17 {
public:
    // Pin modes for the whole bus.
    static const uint8_t PIN_MODE_INPUT = 0xFF;
    static const uint8_t PIN_MODE_OUTPUT = 00;

    MCP23S17(uint8_t cs_pin, spi_inst_t* spi_port, uint8_t address);

    void write_register(uint8_t reg, uint8_t value);
    uint8_t read_register(uint8_t reg);

    // Set pin modes (input/output) for the whole GPIO line.
    void set_pin_mode_gpioa(uint8_t mode);
    void set_pin_mode_gpiob(uint8_t mode);

    // The same for particular pins.
    void set_pin_mode_gpioa(uint8_t gpio_reg, uint8_t pin, bool mode);
    void set_pin_mode_gpiob(uint8_t gpio_reg, uint8_t pin, bool mode);    

    // Enable/disable pullups.
    void enable_pullups_gpioa(bool enable);
    void enable_pullups_gpiob(bool enable);

    // Redd the whole bus.
    uint8_t read_gpioa();
    uint8_t read_gpiob();

    // Write the whole bus.
    void write_pin_gpioa(uint8_t value);
    void write_pin_gpiob(uint8_t value);

    // Writing the particular pins.
    void write_pin_gpioa(uint8_t pin, bool value);
    void write_pin_gpiob(uint8_t pin, bool value);    

private:
    uint8_t cs_pin;
    spi_inst_t* spi_port;
    uint8_t address;

    // Common logic for setting the PIN mode.
    void do_set_pin_mode(uint8_t gpio_reg, uint8_t pin, bool mode);

    // The same for writing to particular GPIO pin.
    void do_write_gpio_pin(uint8_t gpio_reg, uint8_t pin, bool value);

public:
    // Constants for GPIO ports
    static const uint8_t IODIRA = 0x00;
    static const uint8_t IODIRB = 0x01;
    static const uint8_t GPPUA = 0x0C;
    static const uint8_t GPPUB = 0x0D;
    static const uint8_t GPIOA = 0x12;
    static const uint8_t GPIOB = 0x13;
};

#endif // MCP23S17_H
