cmake_minimum_required(VERSION 3.13)
project(BioInf)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


add_executable(BioInf main.cpp Define.h solver.cpp solver.h AbstractGraphBuildStrategy.h AbstractGraphGoThroughStrategy.h Element.cpp Element.h StandardGraphBuild.cpp StandardGraphBuild.h StandardGraphGoThrough.cpp StandardGraphGoThrough.h)
target_link_libraries(${PROJECT_NAME} stdc++fs)
