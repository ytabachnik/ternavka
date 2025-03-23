#include "Configuration.h"
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <cstring>

Configuration::Configuration() : feedSettings(), encoderSettings(), stepMotorSettings() {}

FeedSettings& Configuration::getFeedSettings() {
    return feedSettings;
}

EncoderSettings& Configuration::getEncoderSettings() {
    return encoderSettings;
}

StepMotorSettings& Configuration::getStepMotorSettings() {
    return stepMotorSettings;
}

void Configuration::reset() {
    feedSettings.reset();
    encoderSettings.reset();
    stepMotorSettings.reset();
}

void Configuration::loadFromFlash() {
    uint8_t savedData[sizeof(Configuration)];
    std::memcpy(savedData, (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET), sizeof(Configuration));

    size_t offset = 0;
    offset += feedSettings.load(savedData + offset);
    offset += encoderSettings.load(savedData + offset);
    offset += stepMotorSettings.load(savedData + offset);
}

void Configuration::saveToFlash() {
    uint8_t savedData[sizeof(Configuration)];

    size_t offset = 0;
    offset += feedSettings.save(savedData + offset);
    offset += encoderSettings.save(savedData + offset);
    offset += stepMotorSettings.save(savedData + offset);

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, savedData, sizeof(Configuration));
    restore_interrupts(ints);
}