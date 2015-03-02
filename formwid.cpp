#include "formwid.h"
#include "ui_formwid.h"
#include <QColor>
#include <QImage>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

FormWid::FormWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWid)
{
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

    ui->setupUi(this);
}

FormWid::~FormWid()
{
    delete ui;
}
