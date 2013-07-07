CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
PROJECT(phantompy)

SET(CMAKE_BUILD_TYPE "Release")
#SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(BUILD_SHARED_LIBS ON)

SET(CMAKE_CXX_FLAGS         "-Wall -fPIC")
SET(CMAKE_CXX_FLAGS_DEBUG   "-O3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

IF(APPLE)
    set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    FIND_PROGRAM(HAS_BREW_COMMAND brew)
    IF(HAS_BREW_COMMAND)
        execute_process(COMMAND brew list qt5
            ERROR_VARIABLE QT5_MISSING
            OUTPUT_VARIABLE QT5_FILES
            ERROR_STRIP_TRAILING_WHITESPACE)

        IF(NOT(QT5_MISSING))
            execute_process(COMMAND brew --prefix qt5
                OUTPUT_VARIABLE BREW_QT5_PREFIX
                RESULT_VARIABLE NONZERO_BREW_EXIT_CODE
                ERROR_VARIABLE BREW_ERROR 
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_STRIP_TRAILING_WHITESPACE)
            IF(NOT(NONZERO_BREW_EXIT_CODE))
                SET(CMAKE_PREFIX_PATH ${BREW_QT5_PREFIX})
            ELSE()
                MESSAGE(FATAL_ERROR "Brew reported an error:\n${BREW_ERROR}.\nPlease resolve this error.")
            ENDIF()
        ELSE()
            MESSAGE(FATAL_ERROR "Brew reported that QT5 is not installed, error: ${QT5_MISSING}")
        ENDIF()
    ELSE()
        MESSAGE("Detected OSX but not brew. Assuming QT5 is within default search path. CMake will complain!")
    ENDIF()
ENDIF()

FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Network)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5WebKit)
FIND_PACKAGE(Qt5WebKitWidgets)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5WebKit_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5WebKitWidgets_EXECUTABLE_COMPILE_FLAGS}")

# Add include directories
INCLUDE_DIRECTORIES(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKit_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    lib
)

# Use the compile definitions defined in the Qt 5 Widgets module
ADD_DEFINITIONS(${Qt5Core_DEFINITIONS})
ADD_DEFINITIONS(${Qt5Network_DEFINITIONS})
ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
ADD_DEFINITIONS(${Qt5WebKit_DEFINITIONS})
ADD_DEFINITIONS(${Qt5WebKitWidgets_DEFINITIONS})

IF(CMAKE_BUILD_TYPE MATCHES Release)
    MESSAGE(STATUS "Release build")
    ADD_DEFINITIONS(-DQT_NO_DEBUG)
    ADD_DEFINITIONS(-DQT_NO_DEBUG_OUTPUT)
ELSE()
    MESSAGE(STATUS "Debug build")
ENDIF()


SET(QJSON_SRCS
    lib/qjson/parser.cpp
    lib/qjson/qobjecthelper.cpp
    lib/qjson/json_scanner.cpp
    lib/qjson/json_parser.cc
    lib/qjson/parserrunnable.cpp
    lib/qjson/serializer.cpp
    lib/qjson/serializerrunnable.cpp
)

SET(PHANTOMPY_SOURCES
    lib/phantompy.cpp
    lib/private/context.cpp
    lib/private/page.cpp
    lib/private/frame.cpp
    lib/private/image.cpp
    lib/private/webelement.cpp
    lib/private/webelementcollection.cpp
    lib/private/cookiejar.cpp
    lib/private/networkmanager.cpp
    lib/private/networktimeout.cpp
    lib/private/networkmanagerproxy.cpp
    lib/private/timeout.cpp
    lib/private/eventprocessor.cpp
)

ADD_LIBRARY(phantompy ${QJSON_SRCS} ${PHANTOMPY_SOURCES})

TARGET_LINK_LIBRARIES(
    phantompy
    ${Qt5Core_LIBRARIES}
    ${Qt5Network_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5WebKitWidgets_LIBRARIES}
)

SET_TARGET_PROPERTIES(phantompy PROPERTIES VERSION 0.0.1)

SET(CMAKE_INSTALL_PREFIX /usr)
INSTALL(TARGETS phantompy DESTINATION lib/)
#SET_TARGET_PROPERTIES(phantompy PROPERTIES
#    SUFFIX ".so"
#    PREFIX "_"
#)
#
