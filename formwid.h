#ifndef FORMWID_H
#define FORMWID_H

#include <QWidget>

namespace Ui {
class FormWid;
}

class FormWid : public QWidget
{
    Q_OBJECT

public:
    explicit FormWid(QWidget *parent = 0);
    ~FormWid();

private:
    Ui::FormWid *ui;
};

#endif // FORMWID_H
