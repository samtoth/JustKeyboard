//
// Created by Sam on 15/02/2020.
//

#include <QtWidgets/QMessageBox>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    setWindowTitle(tr("A Keyboard in Just Intonation"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, QColor(0x141a21));

    setupMenuBar();

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


    audioManager = new AudioManager();
    audioManager->moveToThread(&audioThread);
    connect(this, &MainWindow::startAudio,
            audioManager, &AudioManager::start);
    connect(&audioThread, &QThread::finished, audioManager, &QObject::deleteLater);
    connect(kbd1, &KeyboardWidget::setFreq, audioManager, &AudioManager::setStringPitch);
    audioThread.start();
    //audioThread.setPriority(QThread::TimeCriticalPriority);
    startAudio();

}

MainWindow::~MainWindow() {
    audioThread.quit();
    audioThread.wait();
}

void MainWindow::setupMenuBar() {

    audioMenu = menuBar()->addMenu(tr("&Options"));
    audioMenu->addAction(tr("Audio Settings"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("Help"));
    helpMenu->addSeparator();
    aboutAc = helpMenu->addAction(tr("About"));
    connect(aboutAc, &QAction::triggered, [this]() {

        QMessageBox::about(this, tr("About"), tr("A <a href=\"https://github.com/qoolander/JustKeyboard\"><b>Just Intonation Keyboard</b></a> "
                                                                                          "by Sam Toth."));
    });
}


