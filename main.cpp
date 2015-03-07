#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include "formwid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormWid *w = new FormWid();
    w->show();

    return a.exec();
}
