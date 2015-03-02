#include "formwid.h"
#include "ui_formwid.h"


FormWid::FormWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWid)
{
/*    QImage image(3, 3, QImage::Format_Indexed8);
     QRgb value;

     value = qRgb(122, 163, 39); // 0xff7aa327
     image.setColor(0, value);

     value = qRgb(237, 187, 51); // 0xffedba31
     image.setColor(1, value);

     value = qRgb(189, 149, 39); // 0xffbd9527
     image.setColor(2, value);
  */

     gridLayout = new QGridLayout();
         inputImg = new QImage("ksh.png");
         QPainter p;
         p.begin(inputImg);
         p.drawLine( 0,0,10,10 );
         p.end();
         imgDisplayLabel = new QLabel("");
         imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
         imgDisplayLabel->adjustSize();
         scrollArea = new QScrollArea();
         scrollArea->setWidget(imgDisplayLabel);
         scrollArea->setMinimumSize(50,50);
         scrollArea->setMaximumSize(512,512);
         gridLayout->addWidget(scrollArea,0,0);
         //this->layout(gridLayout);
         //this->layout() = gridLayout;
         //this->layout()->deleteLater();
         setLayout(gridLayout);
         int temp;
         QRgb rgd = inputImg->pixel(1,1);
         QColor* col = new QColor(rgd);
         temp = col->black();
    ui->setupUi(this);
}

FormWid::~FormWid()
{
    delete ui;
}

void FormWid::paintEvent(QPaintEvent *) {
    //QBrush b();
    //b.setColor(Qt::black);

    QPainter p;
    p.begin(inputImg);
    //p.drawLine( 0,0,10,10 );

    /*
    QPainter p(); // Создаём новый объект рисовальщика
    p.begin(inputImg);*/
    p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    p.drawLine(0,0,width(),height()); // Рисование линии*/
    p.end();
}
