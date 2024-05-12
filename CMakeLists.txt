cmake_minimum_required(VERSION 3.28)
project(megatron)

set(CMAKE_CXX_STANDARD 17)

add_executable(megatron main.cpp
        Megatron.cpp
        Megatron.h
        Query_Processor/Parser.cpp
        Query_Processor/Parser.h
        Storage_Manager/DiskManager.cpp
        Storage_Manager/DiskManager.h
        Util/myFunc.h
        Util/myFunc.cpp
        Storage_Manager/StorageManager.cpp
        Storage_Manager/StorageManager.h
        Storage_Manager/FileManager.cpp
        Storage_Manager/FileManager.h)
