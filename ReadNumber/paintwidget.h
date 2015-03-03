#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QList>
#include <QtCore/QPoint>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    QList<QPoint> mDrawBuffer;
    bool mDrawMode;
};

#endif // PAINTWIDGET_H
