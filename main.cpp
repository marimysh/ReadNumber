#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include "formwid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	FormWid *w = new FormWid();
    //MainWindow w;
    w->show();

    return a.exec();
}
