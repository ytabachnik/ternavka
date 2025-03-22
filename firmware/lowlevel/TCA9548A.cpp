#include "TCA9548A.h"

TCA9548A::TCA9548A(i2c_inst_t* i2c_port, uint8_t address) : _i2c_port(i2c_port), _address(address) {}

void TCA9548A::selectChannel(uint8_t channel) {
    if (channel > 7) return; // TCA9548A has 8 channels (0-7)
    uint8_t data = 1 << channel;
    i2c_write_blocking(_i2c_port, _address, &data, 1, false);
}

void TCA9548A::writeToDevice(uint8_t deviceAddress, uint8_t data) {
    i2c_write_blocking(_i2c_port, deviceAddress, &data, 1, false);
}

uint8_t TCA9548A::readFromDevice(uint8_t deviceAddress) {
    uint8_t data;
    i2c_read_blocking(_i2c_port, deviceAddress, &data, 1, false);
    return data;
}
