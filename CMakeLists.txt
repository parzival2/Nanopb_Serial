cmake_minimum_required(VERSION 3.0.0)
project(Nanopb_Serial VERSION 0.1.0)
set(CHIBIOS_BOARD_CMAKE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/os/hal/boards/STM32F103C8_MINIMAL/board.cmake)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=false -DOSAL_DBG_ENABLE_CHECKS=false")
else()
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=true -DOSAL_DBG_ENABLE_CHECKS=true")
endif()

# Register headers that we are using so that the IDE will recognize them.
set(HEADERS
    chconf.h
    halconf.h
    mcuconf.h
    LedBlinkerThread.hpp
    proto/messages.proto)

# Sources
set(SOURCES
    usbcfg.c
    main.cpp)

# Include chibios
include(${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/chibios.cmake)

set(PYTHON_EXECUTABLE "/usr/bin/python3")

# Nanopb
set(NANOPB_SRC_ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/nanopb)
set(NANOPB_OPTIONS proto/messages.options)
# Set cmake module path to find nanopb
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${NANOPB_SRC_ROOT_FOLDER}/extra)
# find nanopb
find_package(Nanopb REQUIRED)
# Generate sources and headers
nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS proto/messages.proto)
message(${PROTO_SRCS} "Generated Sources")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${NANOPB_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
# Add the
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_chibios_executable(Nanopb_Serial
                        ${PROTO_SRCS}
                        ${PROTO_HDRS}
                        ${HEADERS}
                        ${SOURCES})
