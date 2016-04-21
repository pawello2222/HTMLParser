cmake_minimum_required(VERSION 3.3)
project(HTMLParser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Scanner/Scanner.cpp "src/Data Structures/Token.cpp" src/Parser/Parser.cpp src/Exceptions/Exceptions.cpp src/Writer/Writer.cpp "src/Data Structures/Tree.cpp" "src/Data Structures/Tree.h" "src/Data Structures/JSONObject.cpp" "src/Data Structures/JSONObject.h")
add_executable(HTMLParser ${SOURCE_FILES})