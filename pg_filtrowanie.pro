 #-------------------------------------------------
#
# Project created by QtCreator 2014-03-17T13:24:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pg_filtrowanie
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        MainWindow.cpp \
    ImagesDialog.cpp \
    FilterDialog.cpp \
    ProcessingEngine.cpp

HEADERS  += MainWindow.hpp \
    ImagesDialog.hpp \
    FilterDialog.hpp \
    ProcessingEngine.hpp

FORMS    += MainWindow.ui \
    ImagesDialog.ui \
    FilterDialog.ui

INCLUDEPATH += C:\\opencv-248\\opencv-build\\install\\include
#LIBS += -LC:\\opencv-248\\opencv-build\\install\\x86\\mingw\\bin \
#LIBS += -LC:\\opencv-248\\opencv-build\\bin \
LIBS += -LC:\\opencv-248\\opencv-build\\install\\x64\\mingw\\bin \
    libopencv_core248 \
    libopencv_highgui248 \
    libopencv_imgproc248 \
    libopencv_imgproc248 \
    libopencv_features2d248 \
    libopencv_calib3d248
