#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>

class QPaintEvent;

class QPaintWidget : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QPaintWidget(QWidget *parent = 0);
    ~QPaintWidget();
protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // QPAINTWIDGET_H
