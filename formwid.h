#ifndef FORMWID_H
#define FORMWID_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPainter>
#include <QBrush>

namespace Ui {
class FormWid;
}

class FormWid : public QWidget
{
    Q_OBJECT

public:
    explicit FormWid(QWidget *parent = 0);
    ~FormWid();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::FormWid *ui;
    QGridLayout* gridLayout;
    QImage* inputImg;
    QLabel* imgDisplayLabel;
    QScrollArea* scrollArea;
};

#endif // FORMWID_H
