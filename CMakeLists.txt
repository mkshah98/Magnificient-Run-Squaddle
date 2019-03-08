cmake_minimum_required(VERSION 3.13)
project(CursesWrapper LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)

add_library(CursesWrapper STATIC
        Window.h
        RowReference.cpp RowReference.h
        WindowImplementation.cpp WindowImplementation.h
        CellReference.cpp CellReference.h)
target_compile_options(CursesWrapper PRIVATE -Wall -Werror)
target_include_directories(CursesWrapper PUBLIC .)

if (${USE_REAL_CURSES})
    set(CURSES_USE_NCURSES TRUE)
    find_package(Curses REQUIRED)
    target_link_libraries(CursesWrapper PUBLIC ${CURSES_LIBRARIES})
    target_include_directories(CursesWrapper PUBLIC ${CURSES_INCLUDE_DIRS})
    target_compile_definitions(CursesWrapper PRIVATE USE_REAL_CURSES)
else ()
    #use fake curses for testing
    target_link_libraries(CursesWrapper PUBLIC FakeCurses)
endif ()
