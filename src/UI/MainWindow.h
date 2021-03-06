//
// Created by Sam on 15/02/2020.
//

#ifndef TRADE_MAINWINDOW_H
#define TRADE_MAINWINDOW_H

#include <QMainWindow>
#include <Audio/AudioManager.h>
#include <QtCore/QThread>
#include <QDesktopWidget>
#include "KeyboardWidget.h"
#include <QHBoxLayout>
#include <qdebug.h>
#include <QMenuBar>

#define A 110

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread audioThread;
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    virtual ~MainWindow();

private:
    AudioManager* audioManager;
    QMenu* audioMenu;
    QMenu* helpMenu;
    QAction* aboutAc;
    void setupMenuBar();
signals:
    void startAudio();
};


#endif //TRADE_MAINWINDOW_H
