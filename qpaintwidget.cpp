#include "qpaintwidget.h"
#include <QBrush>

QPaintWidget::QPaintWidget(QWidget *parent) : QGraphicsScene(parent)
{
}

QPaintWidget::~QPaintWidget()
{
}

void QPaintWidget::paintEvent(QPaintEvent *) {
    //QBrush b();
    //b.setColor(Qt::black);
   
    /*QPainter p(); // Создаём новый объект рисовальщика
    p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    p.drawLine(0,0,width(),height()); // Рисование линии
*/
}
