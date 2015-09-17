
# Target

set(target cg-sandbox)


# Announce target

message(STATUS "Application ${target}")


# External packages

find_package(Qt5Core    5.1 REQUIRED)
find_package(Qt5Gui     5.1 REQUIRED)
find_package(Qt5Widgets 5.1 REQUIRED) # this is important in order to get uic working 
find_package(Qt5OpenGL  5.1 REQUIRED)
find_package(ASSIMP         REQUIRED)


# Includes

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${ASSIMP_INCLUDE_DIRS}
    ${GLBINDING_INCLUDE_DIRS}
    ${GLOBJECTS_INCLUDE_DIRS}
    ${LIBZEUG_INCLUDE_DIRS}
)


# Libraries

set(libs
    ${ASSIMP_LIBRARIES}
)


# Sources

set(sources
    main.cpp
    
    ui/Application.cpp
    ui/Application.h
    ui/Viewer.cpp
    ui/Viewer.h
    ui/Viewer.ui
    
    painter/AbstractPainter.cpp
    painter/AbstractPainter.h
    painter/Painter.cpp
    painter/Painter.h
    
    util/ChronoTimer.cpp
    util/ChronoTimer.h
    util/CyclicTime.cpp
    util/CyclicTime.h
)


# Build executable

list_extract(uis ".*\\\\.ui$" ${sources})

qt5_wrap_ui(uihs ${uis})

add_executable(${target} ${sources} ${uihs})

target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core Gui Widgets OpenGL)

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")


# Deployment

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
)
