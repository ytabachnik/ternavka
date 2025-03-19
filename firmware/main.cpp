#include "pico/stdlib.h"
#include "MCP23S17.h"
#include <stdio.h>

#define CS_PIN 5 // pin 7 on Pico
#define SPI_PORT spi0
#define MCP23S17_ADDR 0x20

int main() {
    stdio_init_all();
    MCP23S17 mcp23s17(CS_PIN, SPI_PORT, MCP23S17_ADDR);

    // Enable pull-up resistors on GPIOA and GPIOB
    mcp23s17.enable_pullups_gpioa(true);
    mcp23s17.enable_pullups_gpiob(false);

    mcp23s17.set_pin_mode_gpioa(0xFF); //input
    mcp23s17.set_pin_mode_gpiob(0x00); //output
    
    while (true) {
        uint8_t gpioa_state = mcp23s17.read_gpioa();  // Read GPIOA
        mcp23s17.write_pin_gpiob(~gpioa_state);
        sleep_ms(100);
    }

    return 0;
}