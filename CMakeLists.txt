cmake_minimum_required(VERSION 3.3)
project(HTMLParser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Scanner/Scanner.cpp src/Scanner/Scanner.h "src/Data Structures/OrderedDict.cpp" "src/Data Structures/OrderedDict.h" "src/Data Structures/Token.cpp" "src/Data Structures/Token.h")
add_executable(HTMLParser ${SOURCE_FILES} src/Scanner/Scanner.cpp src/Scanner/Scanner.h "src/Data Structures/OrderedDict.cpp" "src/Data Structures/OrderedDict.h" "src/Data Structures/Token.cpp" "src/Data Structures/Token.h")