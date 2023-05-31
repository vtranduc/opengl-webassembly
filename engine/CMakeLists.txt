cmake_minimum_required(VERSION 3.26.3)

# Project name
project(engine)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

# Exported functions
set(
    ENGINE_EXPORTED_FUNCTIONS
    _sayHello
)

list(JOIN ENGINE_EXPORTED_FUNCTIONS "," COMMA_EXPORTED_FUNCTIONS)

# Settings
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-sEXPORTED_FUNCTIONS=[${COMMA_EXPORTED_FUNCTIONS}] -sEXPORTED_RUNTIME_METHODS=[ccall,cwrap,addFunction,UTF8ToString]")
