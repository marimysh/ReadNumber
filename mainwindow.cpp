#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QImage>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QImage im =
    int temp;
    //QRgb rgd = new QRgb();
    //QColor col = new QColor(rgd);
    //temp = col.black();

    QImage image(3, 3, QImage::Format_Indexed8);
     QRgb value;

     value = qRgb(122, 163, 39); // 0xff7aa327
     image.setColor(0, value);

     value = qRgb(237, 187, 51); // 0xffedba31
     image.setColor(1, value);

     value = qRgb(189, 149, 39); // 0xffbd9527
     image.setColor(2, value);
     QGridLayout* gridLayout;
         QImage* inputImg;
         QLabel* imgDisplayLabel;
         QScrollArea* scrollArea;

     gridLayout = new QGridLayout();
         inputImg = new QImage("ksh.png");
         imgDisplayLabel = new QLabel("");
         imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
         imgDisplayLabel->adjustSize();
         scrollArea = new QScrollArea();
         scrollArea->setWidget(imgDisplayLabel);
         scrollArea->setMinimumSize(256,256);
         scrollArea->setMaximumSize(512,512);
         gridLayout->addWidget(scrollArea,0,0);
         //this->layout(gridLayout);
         //this->layout() = gridLayout;
         //this->layout()->deleteLater();
         setLayout(gridLayout);

     /*wgt = new QPaintWidget(this);

    QLayout * layout = new QVBoxLayout();
    QGraphicsView * view = new QGraphicsView();
    layout->addWidget(view);
    QWidget * w = new QWidget();
    w->setLayout(layout);
    w->show();*/

    // И кладём его в лайаут
    //ui->verticalLayout->addWidget(wgt);
}

MainWindow::~MainWindow()
{
    // Подчищаем
    //wgt->deleteLater();
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
