//
// Created by Sam on 15/02/2020.
//

#ifndef TRADE_MAINWINDOW_H
#define TRADE_MAINWINDOW_H

#include <QMainWindow>
#include <Audio/AudioManager.h>
#include <QtCore/QThread>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread audioThread;
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    virtual ~MainWindow();

private:
    AudioManager* audioManager;
public slots:
    void setFrequency(int string, float freq);
signals:
    void startAudio();
};


#endif //TRADE_MAINWINDOW_H
