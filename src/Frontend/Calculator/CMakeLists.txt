cmake_minimum_required(VERSION 3.5)

project(Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
    ../../Backend/controller/s21_calc_controller.h
    ../../Backend/controller/s21_deposit_controller.h
    ../../Backend/controller/s21_credit_controller.h

    ../../Backend/model/s21_calc_model.h
    ../../Backend/model/s21_credit_model.h
    ../../Backend/model/s21_deposit_model.h

    # ../../Backend/controller/s21_calc_controller.cc
    # ../../Backend/controller/s21_credit_controller.cc
    # ../../Backend/controller/s21_deposit_controller.cc

    # ../../Backend/model/calc_model_cc/s21_checker.cc
    # ../../Backend/model/calc_model_cc/s21_dijkstra.cc
    # ../../Backend/model/calc_model_cc/s21_getLexems.cc
    # ../../Backend/model/calc_model_cc/s21_stack.cc

    # ../../Backend/model/deposit_model_cc/s21_deposit.cc
    # ../../Backend/model/credit_model_cc/s21_credit.cc

        main.cc
        mainwindow.cc
        secondwindow.cc
        qcustomplot.cc
        mainwindow.h
        secondwindow.h
        qcustomplot.h
        mainwindow.ui
        secondwindow.ui
)
#------------------------------------
set(CALC_LIB_PATH "${CMAKE_SOURCE_DIR}/../../calc.a")
message(STATUS "Path to calc.a: ${CALC_LIB_PATH}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        qcustomplot.cc qcustomplot.h
        secondwindow.h secondwindow.cc secondwindow.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Calculator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Calculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_library(calc STATIC IMPORTED)
set_target_properties(calc PROPERTIES IMPORTED_LOCATION ${CALC_LIB_PATH})

target_link_libraries(Calculator PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(Calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#--------------------
target_link_libraries(Calculator PRIVATE calc)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Calculator)
endif()
set_target_properties(Calculator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Calculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calculator)
endif()
