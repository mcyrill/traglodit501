cmake_minimum_required(VERSION 3.25)
project(traglodit501)

set(CMAKE_CXX_STANDARD 14)

add_executable(traglodit501
        src/main.cpp src/exceptions/exceptions.h src/decoder/decoder.h src/decoder/decoder.cpp src/encoder/encoder.h src/encoder/encoder.cpp src/argparse/Command.h)