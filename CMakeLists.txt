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
        Query_Processor/ExecutionEngine.cpp
        Query_Processor/ExecutionEngine.h
        Query_Processor/Schema.cpp
        Query_Processor/Schema.h
        Query_Processor/Page.cpp
        Query_Processor/Page.h
)
