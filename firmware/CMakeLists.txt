cmake_minimum_required(VERSION 3.12)

project(ternavka C CXX ASM)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

pico_sdk_init()

add_executable(ternavka
    main.cpp
    lowlevel/MCP23S17.cpp
    lowlevel/TCA9548A.cpp

    hal/LEDManager.cpp
    hal/KeyboardManager.cpp
    hal/MultiDisplayManager.cpp

    CurrentTimeManager.cpp
)

add_subdirectory(libs/pico-ssd1306)

target_include_directories(ternavka PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
     hal
     lowlevel
     libs/pico-ssd1306
)

# pull in common dependencies
target_link_libraries(ternavka pico_stdlib hardware_i2c hardware_spi pico_ssd1306)

# create map/bin/hex file etc.
pico_add_extra_outputs(ternavka)
