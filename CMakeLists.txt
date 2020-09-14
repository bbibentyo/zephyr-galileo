cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(galileo)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
