cmake_minimum_required(VERSION 3.13)
project(phpPi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(phpPi
        tests/001.phpt
        config.m4
        config.w32
        CREDITS
        EXPERIMENTAL
        php_phpPi.h
        phpPi.c
        phpPi.php)
