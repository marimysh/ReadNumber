#include "paintwidget.h"

#include <QtCore/QLine>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QPen>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    mDrawMode = false;
}

PaintWidget::~PaintWidget()
{

}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = true;
        mDrawBuffer.append(event->pos());
        //mDrawBuffer.append(0);
        event->accept();
        //mDrawBuffer.clear();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = false;
        mDrawBuffer.append(event->pos());
        this->update();
        event->accept();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mDrawMode) return;
    mDrawBuffer.append(event->pos());
    this->update();
    event->accept();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    if (mDrawBuffer.size()<1) return;
    QPen pen = QPen();
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    QPainter painter(this);
    painter.setPen(pen);
    //painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QList<QPoint>::const_iterator it = mDrawBuffer.begin();
    QPoint start = *it;
    it++;
    //QList<QPoint>::const_iterator it2 = mDrawBuffer.end();
    //QPoint end = *it2;
    painter.drawLine(start,start);

    //it++;
    //while (true)
    //{
        while(it != mDrawBuffer.end()) {
            QPoint end = *it;
            painter.drawLine(start,end);
            start = end;
            it++;
        }
        //mDrawBuffer.clear();
        //it = mDrawBuffer.begin();
    //}
        --it;

}
