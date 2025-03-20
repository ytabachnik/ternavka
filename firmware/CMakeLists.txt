cmake_minimum_required(VERSION 3.12)

project(ternavka C CXX ASM)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR}/hal)
include_directories(${CMAKE_SOURCE_DIR}/lowlevel)

add_subdirectory(libs/pico-ssd1306)

add_executable(ternavka
    main.cpp
    lowlevel/MCP23S17.cpp
    hal/LEDManager.cpp
    hal/KeyboardManager.cpp
)

target_include_directories(ternavka
    PRIVATE ${PICO_SDK_PATH}/src/rp2_common/hardware/i2c/include
    PRIVATE ${PICO_SDK_PATH}/src/rp2_common/hardware/spi/include
    PRIVATE ${CMAKE_SOURCE_DIR}/libs/pico-ssd1306
    )

# pull in common dependencies
target_link_libraries(ternavka pico_stdlib hardware_i2c hardware_spi ssd1306)

# create map/bin/hex file etc.
pico_add_extra_outputs(ternavka)
