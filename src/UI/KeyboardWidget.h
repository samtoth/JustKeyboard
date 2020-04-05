//
// Created by Sam on 15/02/2020.
//

#ifndef TRADE_KEYBOARDWIDGET_H
#define TRADE_KEYBOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class KeyboardWidget : public QWidget{
Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = Q_NULLPTR);

    int getFundFreq() const {return fundFreq;}

    void setFundFreq(int fundFreq) {KeyboardWidget::fundFreq = fundFreq;}

    void kill();
protected:
    void paintEvent( QPaintEvent *e );
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;

    QString labels[13] = {"5/7", "6/7", "4/7", "3/5", "4/5", "2/3", "1", "3/2", "5/4", "5/3", "7/4", "7/6", "7/5"};
    int numerators[13] = {5,6,4,3,4,2,1,3,5,5,7,7,7};
    int denominators[13]={7,7,7,5,5,3,1,2,4,3,4,6,5};
private:
    bool getStringAndFreq(int *string, float *frequency, QPointF point);
    QString toFrac(int n, int d);
    void reduce(int *n, int *d);
    float ratios(int i);
    int fundFreq;
    int space;
    int bar;
    bool shift;
signals:
    void setFreq(int string, float freq);
};


#endif //TRADE_KEYBOARDWIDGET_H
