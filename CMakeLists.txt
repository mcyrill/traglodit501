cmake_minimum_required(VERSION 3.25)
project(traglodit501)

set(CMAKE_CXX_STANDARD 14)

add_executable(traglodit501
        src/main.cpp src/exceptions/exceptions.h src/decoder/decoder.h src/decoder/decoder.cpp src/encoder/encoder.h src/argparse/Command.h src/encoder/HuffmanTree/Node.h src/encoder/HuffmanTree/HuffmanTree.h src/encoder/HuffmanTree/HuffmanTree.cpp src/types.h)