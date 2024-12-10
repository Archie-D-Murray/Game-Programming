cmake_minimum_required(VERSION 3.24)
project(SFML-Test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_CXX_STANDARD 20)


file(GLOB PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-system sfml-window sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/ucrt\"")
    add_custom_command(
      TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
    add_custom_command(
      TARGET ${PROJECT_NAME}
        COMMENT "Copying output to source dir"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            "${CMAKE_SOURCE_DIR}"
    )
endif()
