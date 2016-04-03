cmake_minimum_required(VERSION 3.3)
project(HTMLParser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Scanner.cpp Scanner.h OrderedDict.cpp OrderedDict.h)
add_executable(HTMLParser ${SOURCE_FILES} Scanner.cpp Scanner.h OrderedDict.cpp OrderedDict.h)