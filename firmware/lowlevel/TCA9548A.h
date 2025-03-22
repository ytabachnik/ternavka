#ifndef TCA9548A_H
#define TCA9548A_H

#include "hardware/i2c.h"

class TCA9548A {
public:
    TCA9548A(i2c_inst_t* i2c_port, uint8_t address);
    void selectChannel(uint8_t channel);
    void writeToDevice(uint8_t deviceAddress, uint8_t data);
    uint8_t readFromDevice(uint8_t deviceAddress);

private:
    i2c_inst_t* _i2c_port;
    uint8_t _address;
};

#endif
