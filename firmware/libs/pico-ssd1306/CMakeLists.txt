# CMakeLists.txt for the ssd1306 library
cmake_minimum_required(VERSION 3.13)

# Define the library
add_library(ssd1306 STATIC
    ssd1306.c
)

# Include directories for the library
target_include_directories(ssd1306 
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE ${PICO_SDK_PATH}/src/rp2_common/hardware_i2c/include
)

# Link the Pico SDK libraries
target_link_libraries(ssd1306 pico_stdlib)