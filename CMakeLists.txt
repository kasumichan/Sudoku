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

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_executable(Sudoku main.cpp Cell.cpp Cell.h Board.cpp Board.h UI/MainWindow.cpp UI/MainWindow.h UI/BoardPanel.cpp UI/BoardPanel.h UI/CellWidget.cpp UI/CellWidget.h Message.cpp Message.h UI/InfoLabel.cpp UI/InfoLabel.h)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

