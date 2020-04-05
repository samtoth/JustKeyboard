#include <iostream>
#include <thread>
#include <QtWidgets/QApplication>
#include <UI/MainWindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents,false);
    a.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, true);

    MainWindow w;
    w.show();
    w.setWindowState(Qt::WindowMaximized);
    int c = a.exec();
    return c;
}
