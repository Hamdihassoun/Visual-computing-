# http://doc.qt.io/qt-5/qmake-variable-reference.html

QT += core widgets gui
# opengl QT_OPENGL_LIB 

DEFINES += QT_WIDGETS_LIB
INCLUDEPATH += .
#LIBS += -lopengl32 -lglu32
    
HEADERS += plotter.h \
           canvas.h
SOURCES += plotter.cpp \
           canvas.cpp \
           main.cpp
