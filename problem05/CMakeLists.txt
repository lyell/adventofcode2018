project(problem05
    VERSION 1.0.0
    DESCRIPTION "Advent of Code Problem 05")

find_package(Boost COMPONENTS regex)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${Boost_INCLUDE_DIRS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
