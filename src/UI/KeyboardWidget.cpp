//
// Created by Sam on 15/02/2020.
//

#include "KeyboardWidget.h"
#include "Note.h"
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QtCore/QTime>

KeyboardWidget::KeyboardWidget(QWidget *parent) {
    setStyleSheet("background: #111111");
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_AcceptTouchEvents);
}

void KeyboardWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    int w = size().width() - 20;
    int h = size().height() - 20;
    p.setPen( QColor(255,255,255) );
    p.drawLine(0, 0, w, 0 );
    p.drawLine(0, 0, 0, h);
    p.drawLine(w, 0, w, h);
    p.drawLine(0, h, w, h);

    space = w * (1/10.f)*(1/14.f) + 1 ;
    bar = w*(9/10.f)*(1/13.f) + 1;
    int cW = 0;
    for(int i = 0; i<13; i++){
        cW += space;
        p.drawLine(cW, h+20, cW, h);
        int b = 0;
        p.drawLine(cW, h , cW, h- ((ratios(i) * 8)*h));
        int midiCentDiff;
        for(int j =1; j<12; j++) {
            b = h - ((ratios(i) * j) * h/10);
            if(remainderf(log2f(ratios(i)*j), 1.f)==0){
                p.fillRect(cW+1, b, bar-1, (ratios(i) * h/10), QColor(45, 91, 109));
            }else if(remainderf(log2f(ratios(i)*j/3), 1.f)==0){
                p.fillRect(cW+1, b, bar-1, (ratios(i) * h/10), QColor(173, 122, 67));
            }else if(remainderf(log2f(ratios(i)*j/5), 1.f)==0){
                p.fillRect(cW+1, b, bar-1, (ratios(i) * h/10), QColor(168, 65, 75));
            }
            p.setPen(QColor(255,255,255));
            p.drawLine(cW, b, cW + bar -1, b);
            p.drawText(cW+bar - 30, b+20, toFrac(numerators[i]*j, denominators[i]));
            p.drawText(cW+bar/2-5, b+((ratios(i) * 0.5f) * h/10), QString::fromStdString(getNoteName(fundFreq * ratios(i)*j, &midiCentDiff)));
            p.drawText(cW+bar/2-5, b+((ratios(i) * 0.7f) * h/10), QString::number(midiCentDiff));
        }

        cW += bar/2;
        p.drawText(cW -5, h+20, QString(labels[i]));
        cW += bar/2;
        p.drawLine(cW, h, cW, h- ((ratios(i) * 8)*(h+20)));
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
        int n = 0;
        float f = 0.f;
        getStringAndFreq(&n, &f, event->pos());
        setFreq(n, f);
    }
}

void KeyboardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        int n = 0;
        float f = 0.f;
        getStringAndFreq(&n, &f, event->pos());
        setFreq(n, f);
    }
}

void KeyboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!shift){kill();}
}

void KeyboardWidget::kill() {
    for(int i=0; i < 13; i++){
        this->setFreq(i, 0);
    }
}


bool KeyboardWidget::event(QEvent *event){
    switch (event->type()) {
        case QEvent::TouchBegin: {
            return true;
        }
        case QEvent::TouchUpdate: {
            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
            if(!shift){kill();}
            foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
                if(touchPoint.state()!=Qt::TouchPointReleased) {
                    int n = 0;
                    float f = 0.f;
                    getStringAndFreq(&n, &f, touchPoint.pos());
                    setFreq(n, f);
                    continue;
                }
            }
            return true;
        }
        case QEvent::TouchEnd: {
            return true;
        }
        case QEvent::KeyRelease:
        case QEvent::KeyPress: {
            shift = static_cast<QKeyEvent *>(event)->modifiers() == Qt::ShiftModifier;
            if(!shift){kill();}
            break;
        }
        default:
            return QWidget::event(event);
    }
}

bool KeyboardWidget::getStringAndFreq(int *string, float *frequency, QPointF point) {
    int h = size().height() - 20;
    int cX = 0;
    for(int i = 0; i<13; i++) {
        if(point.x() > cX && point.x() <= cX+space)
            return false;
        cX += space;
        if(point.x() > cX && point.x() <= cX+bar) {
            int height = h-point.y();
            int n = ceilf(height/(float)(ratios(i) * h/10));

            *string = i;
            *frequency = fundFreq*ratios(i)*n;
            return true;
        }
        cX += bar;
    }
    return false;
}