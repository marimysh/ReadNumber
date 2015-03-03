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
         //p.drawLine( 0,0,10,10 );
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

    inputImg = new QImage("ksh.png");
    QPainter p;
    //QImage tempImg = imgDisplayLabel->pixmap()->toImage();
    //inputImg = &tempImg;
    p.begin(inputImg);
    p.drawLine( 0,0,10,10 );

    if (mDrawBuffer.size()<1) return;
    QPen penB(Qt::black);
    penB.setCapStyle(Qt::RoundCap);
    // ширина кисти в пикселях
    penB.setWidth(4);

    p.setPen(penB);
    //QPainter painter(this);
    //painter.setPen(penB);
    //painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QList<QPoint>::const_iterator it = mDrawBuffer.begin();
    QPoint start = *it;
    it++;
    //QList<QPoint>::const_iterator it2 = mDrawBuffer.end();
    //QPoint end = *it2;
    //painter.drawLine(start,start);

        while(it != mDrawBuffer.end()) {
            QPoint end = *it;
            //p.drawLine( 1,4,20,20 );
            end.setX(end.rx()-13);
            end.setY(end.ry()-13);
            start = end;
            p.drawPoint(end);
            it++;
        }
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
        //mDrawBuffer.clear();
       p.end();

/*
    //inputImg = new QImage("ksh.png");
    QPainter p; // Создаём новый объект рисовальщика
    p.begin(inputImg);
    p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    p.drawLine(0,0,width(),height()); // Рисование линии
    p.end();*/
}

void FormWid::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = true;
        mDrawBuffer.append(event->pos());
        //mDrawBuffer.append(0);
        event->accept();
        //mDrawBuffer.clear();
    }
}

void FormWid::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = false;
        mDrawBuffer.append(event->pos());
        this->update();
        event->accept();
    }
}

void FormWid::mouseMoveEvent(QMouseEvent *event)
{
    if (!mDrawMode) return;
    mDrawBuffer.append(event->pos());
    this->update();
    event->accept();
}
/*
void PaintWidget::paintEvent(QPaintEvent *event)
{
    if (mDrawBuffer.size()<1) return;
    QPen pen = QPen();
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    QPainter painter(this);
    painter.setPen(pen);
    //painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QList<QPoint>::const_iterator it = mDrawBuffer.begin();
    QPoint start = *it;
    it++;
    //QList<QPoint>::const_iterator it2 = mDrawBuffer.end();
    //QPoint end = *it2;
    painter.drawLine(start,start);

    //it++;
    //while (true)
    //{
        while(it != mDrawBuffer.end()) {
            QPoint end = *it;
            painter.drawLine(start,end);
            start = end;
            it++;
        }
        //mDrawBuffer.clear();
        //it = mDrawBuffer.begin();
    //}
        --it;

}
*/
