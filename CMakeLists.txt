cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)
project(galileo)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_cfb_font_for_target(app img/face_shot_clear.png ${gen_dir}/cfb_image.h 112 96 --first 49 --last 54)
