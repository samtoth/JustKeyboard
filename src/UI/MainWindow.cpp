//
// Created by Sam on 15/02/2020.
//

#include "MainWindow.h"
#include <QDesktopWidget>
#include "KeyboardWidget.h"
#include <QHBoxLayout>
#include <qdebug.h>

#define A 110

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent){
    setWindowTitle(tr("A Keyboard in Just Intonation"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, QColor(0x141a21));


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

    window->setAutoFillBackground(true);
    window->setPalette(pal);

    connect(kbd1, &KeyboardWidget::setFreq, this, &MainWindow::setFrequency);

    audioManager = new AudioManager();
    audioManager->moveToThread(&audioThread);
    connect(this, &MainWindow::startAudio,
            audioManager, &AudioManager::start);
    connect(&audioThread, &QThread::finished, audioManager, &QObject::deleteLater);
    audioThread.start();
    audioThread.setPriority(QThread::TimeCriticalPriority);
    startAudio();
}

MainWindow::~MainWindow() {
    audioThread.quit();
    audioThread.wait();
}

void MainWindow::setFrequency(int string, float freq) {
    audioManager->setStringPitch(string, freq);
}

