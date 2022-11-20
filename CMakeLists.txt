cmake_minimum_required(VERSION 3.10)

set(PROJECT_SOURCES 
    src/Arguments.cpp
    src/ArgumentsFactory.cpp
    src/Command.cpp
    src/HelpCommandInfo.cpp
    src/CommandParser.cpp
    src/CommandsBuilder.cpp
    src/Kernel.cpp
    src/Rules.cpp
    src/curl/RequestHandler.cpp)

set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs -lcurl")
project(dropbox_pi_cli)

#lib for working with json
find_package(nlohmann_json REQUIRED)

#libcurl for making requestss
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} src/main.cpp)

set_target_properties(${PROJECT_NAME}  PROPERTIES CXX_STANDARD 17)

#linking libs
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json ${CURL_LIBRARIES} stdc++fs )

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}
ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION} )

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})



# Link runTests with what we want to test and the GTest and pthread library
add_executable(runAllTests
src/CommandsBuilderTests.cpp
src/CommandParserWithConfigTests.cpp
src/CommandsTests.cpp
src/ArgumentsTests.cpp
src/CommandRulesTests.cpp
src/maintest.cpp
${PROJECT_SOURCES}
)
target_link_libraries(runAllTests ${GTEST_LIBRARIES} ${CURL_LIBRARIES} pthread)