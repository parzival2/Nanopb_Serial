cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.1.0)
set(CHIBIOS_BOARD_CMAKE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/os/hal/boards/STM32F103C8_MINIMAL/board.cmake)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=false -DOSAL_DBG_ENABLE_CHECKS=false")
else()
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=true -DOSAL_DBG_ENABLE_CHECKS=true")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/chibios.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_chibios_executable(Nanopb_Serial
                        chconf.h
                        halconf.h
                        mcuconf.h
                        usbcfg.h
                        usbcfg.c
                        LedBlinkerThread.hpp
                        main.cpp)
