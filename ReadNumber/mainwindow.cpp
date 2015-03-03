#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QImage myImage;
    myImage.load("test.png");

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(myImage));
    QPixmap map = QPixmap::fromImage(myImage);
    map.
    myLabel.show();

    /*
    QGraphicsScene scene;
    scene.addText("54422");
    //ui->view->setScene(&scene);
    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
     int startAngle = 30 * 16;
     int spanAngle = 120 * 16;

     QPainter painter;
     painter.drawPie(rectangle, startAngle, spanAngle);
     QPainter* it = painter.begin();
     ui->view->backgroundBrush().
    ui->setupUi(this);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
