cmake_minimum_required(VERSION 3.28)
project(learning_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(findUniqElement Homeworks-1/findUniqElement.cpp)
add_executable(findTwoUniqElement Homeworks-1/findTwoUniqElement.cpp)
add_executable(2DArrays-DS Homeworks-1/hackerrank/arrays/2DArrays-DS.cpp)
add_executable(LeftRotation Homeworks-1/hackerrank/arrays/LeftRotation.cpp)
add_executable(NewYearChaos Homeworks-1/hackerrank/arrays/NewYearChaos.cpp)
add_executable(MinimumSwaps2 Homeworks-1/hackerrank/arrays/MinimumSwaps2.cpp)
add_executable(ArrayManipulation Homeworks-1/hackerrank/arrays/ArrayManipulation.cpp)
add_executable(vector Homeworks-1/vector/main.cpp)
add_executable(list Homeworks-1/list/main.cpp)
add_executable(insertingANode Homeworks-1/hackerrank/lists/insertingANode.cpp)
add_executable(checkAndTestSorts Homeworks-2/sorts/checkAndTestSorts.cpp)

target_compile_definitions(checkAndTestSorts
        PRIVATE $<$<CONFIG:Debug>:DEBUG>
)
