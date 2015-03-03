#include <QApplication>
#include "mainwindow.h"
#include "paintwidget.h"

#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    PaintWidget w;
    MainWindow w;
    w.show();
    
    return a.exec();
}
