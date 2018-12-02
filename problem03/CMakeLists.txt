project(problem03
    VERSION 1.0.0
    DESCRIPTION "Advent of Code Problem 03")

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

target_link_libraries(${PROJECT_NAME})
