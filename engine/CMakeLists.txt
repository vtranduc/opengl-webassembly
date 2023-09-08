cmake_minimum_required(VERSION 3.26.3)

# Project name
project(engine)


# Exported functions
set(
    ENGINE_EXPORTED_FUNCTIONS
    _sayHello
    _initialize
    _setClearColor
    _usePreset
    _onClearColorChange
    _setColorTriangleColor
    _onColorTriangleUpdated
)

# Include associated files
file(GLOB_RECURSE HEADERS headers/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

# Executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

list(JOIN ENGINE_EXPORTED_FUNCTIONS "," COMMA_EXPORTED_FUNCTIONS)

# Settings
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
    "-sEXPORTED_FUNCTIONS=[${COMMA_EXPORTED_FUNCTIONS}]\
    -sEXPORTED_RUNTIME_METHODS=[ccall,cwrap,addFunction,UTF8ToString]\
    -sALLOW_TABLE_GROWTH\
    -sMIN_WEBGL_VERSION=2\
    -sUSE_SDL=2\
")