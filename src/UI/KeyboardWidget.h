//
// Created by Sam on 15/02/2020.
//

#ifndef TRADE_KEYBOARDWIDGET_H
#define TRADE_KEYBOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class KeyboardWidget : public QWidget{
Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = Q_NULLPTR);

    int getFundFreq() const {return fundFreq;}

    void setFundFreq(int fundFreq) {KeyboardWidget::fundFreq = fundFreq;}

    void kill();
protected:
    void paintEvent( QPaintEvent *e ) override;
    bool event(QEvent *event) override;


private:
    bool getStringAndFreq(int *string, float *frequency, QPointF point);
    QString toFrac(int n, int d);
    void reduce(int *n, int *d);
    int fundFreq;
    int space;
    int bar;
    bool shift;
signals:
    void setFreq(int string, float freq);
};


#endif //TRADE_KEYBOARDWIDGET_H
