//
// Created by Sam on 15/02/2020.
//

#include "KeyboardWidget.h"
#include "Note.h"
#include <QPainter>
#include <cmath>

KeyboardWidget::KeyboardWidget(QWidget *parent) {

}

void KeyboardWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    int w = size().width() - 1;
    int h = size().height() - 1;
    p.setPen( QColor(0,0,0) );
    p.drawLine(0, 0, w, 0 );
    p.drawLine(0, 0, 0, h-20);
    p.drawLine(w, 0, w, h-20);
    p.drawLine(0, h-20, w, h-20);

    h = h- 20;
    int space = w * (1/10.f)*(1/14.f);
    int bar = w*(9/10.f)*(1/13.f);
    int cW = 0;
    for(int i = 0; i<13; i++){
        cW += space;
        p.drawLine(cW, h+20, cW, h);
        int b = 0;
        p.drawLine(cW, h , cW, h- ((ratios(i) * 8)*h));
        int midiCentDiff;
        for(int j =1; j<9; j++) {
            b = h - ((ratios(i) * j) * h/10);
            if(remainderf(log2f(ratios(i)*j), 1.f)==0){
                p.fillRect(cW, b, bar, (ratios(i) * h/10), QColor(45, 91, 109));
            }else if(remainderf(log2f(ratios(i)*j/3), 1.f)==0){
                p.fillRect(cW, b, bar, (ratios(i) * h/10), QColor(173, 122, 67));
            }else if(remainderf(log2f(ratios(i)*j/5), 1.f)==0){
                p.fillRect(cW, b, bar, (ratios(i) * h/10), QColor(168, 65, 75));
            }
            p.setPen(QColor(0,0,0));
            p.drawLine(cW, b, cW + bar, b);
            p.drawText(cW+bar - 30, b+20, toFrac(numerators[i]*j, denominators[i]));
            p.drawText(cW+bar/2-5, b+((ratios(i) * 0.5f) * h/10), QString::fromStdString(getNoteName(fundFreq * ratios(i)*j, &midiCentDiff)));
            p.drawText(cW+bar/2-5, b+((ratios(i) * 0.7f) * h/10), QString::number(midiCentDiff));
        }

        cW += bar/2;
        p.drawText(cW -5, h+20, QString(labels[i]));
        cW += bar/2;
        p.drawLine(cW, h, cW, h- ((ratios(i) * 8)*h+20));
        p.drawLine(cW, h+20, cW, h);
    }



}

float KeyboardWidget::ratios(int i) {
    return numerators[i]/(float)denominators[i];
}

QString KeyboardWidget::toFrac(int n, int d) {
    reduce(&n, &d);
    if(d==1){
        return QString::number(n);
    }
    return QString(QString::number(n) + tr("/") + QString::number(d));
}

void KeyboardWidget::reduce(int *n, int *d) {
    for(int i=2; i<8; i++){
        if(*n%i ==0 && *d%i ==0){
            *n = *n/i;
            *d = *d/i;
            reduce(n, d);
        }
    }
    return;
}

void KeyboardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //lastPoint = event->pos();
        //scribbling = true;
    }
}

void KeyboardWidget::mouseMoveEvent(QMouseEvent *event)
{
    //if ((event->buttons() & Qt::LeftButton) && scribbling)
        //drawLineTo(event->pos());
}

void KeyboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton /*&& scribbling*/) {
        //drawLineTo(event->pos());
        //scribbling = false;
    }
}