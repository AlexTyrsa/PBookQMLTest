cmake_minimum_required(VERSION 3.14)

project(barch LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
        PRIVATE
            libbarch.cpp
            libbarch_chunksize.h
            vector_to_bitmask.h
            vector_to_bitmask.cpp
            barch_header.h
        PUBLIC include/libbarch.h
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE LIBBARCH_LIBRARY)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/../Build"
    )

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "$<TARGET_FILE:${PROJECT_NAME}>"
                "${CMAKE_CURRENT_SOURCE_DIR}/../Build"
    )

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/include"
                "${CMAKE_CURRENT_SOURCE_DIR}/../Build/include/${NEW_FILE_PATH}${FILE_NAME}"
    )
