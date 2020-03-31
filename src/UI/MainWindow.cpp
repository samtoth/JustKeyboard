//
// Created by Sam on 15/02/2020.
//

#include "MainWindow.h"
#include <QDesktopWidget>
#include "KeyboardWidget.h"
#include <QHBoxLayout>

#define A 110

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent){
    setWindowTitle(tr("Main Window by Sam"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    QHBoxLayout *layout = new QHBoxLayout();
    KeyboardWidget *kbd1 = new KeyboardWidget(this);
    kbd1->setFundFreq(A);
    KeyboardWidget *kbd2 = new KeyboardWidget(this);
    kbd2->setFundFreq(A*5 *0.25f);
    layout->addWidget(kbd1);
    layout->addWidget(kbd2);
    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);
}