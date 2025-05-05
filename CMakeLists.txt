cmake_minimum_required(VERSION 3.26)
project(SD_P2)

set(CMAKE_CXX_STANDARD 23)

add_executable(SD_P2 main.cpp
        PriorityQueueLinkedList.h
        PriorityQueueFibonacciHeap.h
        PriorityQueue.h "DynamicArray.h" "MaxHeap.h" "MinHeap.h" "PriorityQueueMinHeap.h" "PriorityQueueMaxHeap.h")
