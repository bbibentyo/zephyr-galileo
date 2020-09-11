cmake_minimum_required(VERSION 3.13.1)
set(BOARD reel_board)

# find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
find_package(Zephyr)
project(galileo)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
