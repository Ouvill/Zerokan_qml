cmake_minimum_required(VERSION 3.6)
project(Zerokan_WT_Flight_Recorder)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
        )

###########################
##         boost
###########################
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem regex system )

if(Boost_FOUND)
    message(STATUS "Boost is ${BOOST_ROOT}")
    message(STATUS "Boost directories found at ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries found at ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost component libraries to be linked are ${Boost_LIBRARIES}")
    message(STATUS "Boost version found is ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
    link_directories("${Boost_LIBRARY_DIRS}")
elseif()
    message("Boost NOT Found!")
endif()

############################
##          Qt
############################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_AUTORCC ON)
# dependency
find_package(Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package(Qt5Gui REQUIRED)
get_target_property(QtCore_location Qt5::Gui LOCATION)
find_package(Qt5Widgets REQUIRED)
get_target_property(QtCore_location Qt5::Widgets LOCATION)
find_package(Qt5Sql)
get_target_property(QtCore_location Qt5::Sql LOCATION)
find_package(Qt5Network REQUIRED)
get_target_property(QtCore_location Qt5::Network LOCATION)
find_package(Qt5 COMPONENTS Qml Quick REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/ui_forms)
qt5_wrap_ui(UIS_HDRS
        src/gui/mainwindow.ui
        src/gui/SettingForm.ui
        )
qt5_add_resources(QRC ${PROJECT_SOURCE_DIR}/Zerokan_WT_Flight_Recorder.qrc)

set(SOURCE_FILES main.cpp
        src/gui/MainWindow.cpp
        src/gui/MainWindow.h
        src/background/BackGround.cpp
        include/BackGround.h
        src/sql/AccessSQL.cpp
        include/AccessSQL.h
        src/background/Setting.cpp
        include/Setting.h
        src/background/http/game_state.cpp
        include/game_state.h
        src/background/http/async_client.cpp
        include/async_client.h
        src/background/user.cpp
        include/user.h
        src/background/GameInfo.cpp include/GameInfo.h
        include/hudmsg_reader.h
        src/background/http/hudmsg_reader.cpp
        include/damages.h
        src/background/http/damages.cpp
        include/picojson.hpp
        include/timer.h
        src/background/http/timer.cpp
        src/gui/SettingForm.cpp src/gui/SettingForm.h)
add_executable(${PROJECT_NAME}  ${UIS_HDRS} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql  Qt5::Network Qt5::Qml Qt5::Quick)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXXFLAGS "${CMAKE_CXX_FLAGS} -no-openssl")

if (WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")
#
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#            COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME})
    target_link_libraries(${PROJECT_NAME} ws2_32)

endif(WIN32)