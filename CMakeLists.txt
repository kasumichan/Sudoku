cmake_minimum_required(VERSION 3.20)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CURRENT_SOURCE_DIR ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.10/5.12.10/mingw73_64")
else ()
    set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")
endif ()

set(CMAKE_BUILD_TYPE Release)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set(APP_ICON_RESOURCE_WINDOWS "Resources/resources.rc")

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_executable(Sudoku main.cpp Game/Cell.cpp Game/Cell.h Game/Board.cpp Game/Board.h UI/MainWindow.cpp UI/MainWindow.h UI/BoardPane.cpp UI/BoardPane.h Controller/CellWidget.cpp Controller/CellWidget.h Message/Message.cpp Message/Message.h UI/InfoPane.cpp UI/InfoPane.h Message/CellData.cpp Message/CellData.h Message/BoardStatus.h Puzzle/Puzzle.h UI/MenuBarPane.cpp UI/MenuBarPane.h UI/LevelSelectPane.cpp UI/LevelSelectPane.h Controller/InfoBtn.cpp Controller/InfoBtn.h Controller/PuzzleMenu.cpp Controller/PuzzleMenu.h Message/PuzzleDegree.h ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})


if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
