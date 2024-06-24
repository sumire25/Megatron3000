cmake_minimum_required(VERSION 3.28)
project(megatron)

set(CMAKE_CXX_STANDARD 17)

add_executable(megatron main.cpp
        Megatron.cpp
        Megatron.h
        Disk_Manager/DiskManager.cpp
        Disk_Manager/DiskManager.h
        Util/myFunc.h
        Util/myFunc.cpp
        Query_Processor/ExecutionEngine.cpp
        Query_Processor/ExecutionEngine.h
        Query_Processor/Schema.cpp
        Query_Processor/Schema.h
        Buffer_Manager/Page.cpp
        Buffer_Manager/Page.h
        Buffer_Manager/BufferPool.cpp
        Buffer_Manager/BufferPool.h
        Buffer_Manager/BufferManager.cpp
        Buffer_Manager/BufferManager.h
        Buffer_Manager/Replacer.h
        Query_Processor/pageEdit.cpp
        Query_Processor/pageEdit.h
)
