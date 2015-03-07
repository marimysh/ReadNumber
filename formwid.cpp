#include "formwid.h"
#include "ui_formwid.h"
#include "iostream"


FormWid::FormWid(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormWid)
{
	gridLayout = new QGridLayout();
	inputImg = new QImage("ksh.png");
	//QPainter p;
	//p.begin(inputImg);
	//p.drawLine( 0,0,10,10 );
	//p.end();
	imgDisplayLabel = new QLabel("");
	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	/*scrollArea = new QScrollArea();
	scrollArea->setWidget(imgDisplayLabel);
	scrollArea->setMinimumSize(50,50);
	scrollArea->setMaximumSize(512,512);
	gridLayout->addWidget(scrollArea,0,0);*/
	gridLayout->addWidget (imgDisplayLabel, 0, 0);
	//QRgb rgd = inputImg->pixel(1,1);
	//QColor* col = new QColor(rgd);
	//temp = col->black();

	recognitionButton = new QPushButton("Recognition", this);
	connect (recognitionButton, SIGNAL(released()), this,
			 SLOT(pressRecognitionButton()));
	gridLayout->addWidget (recognitionButton, 0, 200);
	setLayout(gridLayout);
	ui->setupUi(this);
}

FormWid::~FormWid()
{
	delete ui;
}

void FormWid::paintEvent(QPaintEvent *) {
	QPainter p;
	QImage tempImg = imgDisplayLabel->pixmap()->toImage();
	inputImg = new QImage(tempImg);
	/*
	int pixels = inputImg->width() * inputImg->height();
	if (pixels*(int)sizeof(QRgb) <= inputImg->byteCount())
	{
		QRgb *data = (QRgb *)inputImg->bits();
		for (int i = 0; i < pixels; ++i)
		{
			//int val = qGray(data[i]);
			//data[i] = qRgba(val, val, val, qAlpha(data[i]));
			//std::cout << data[i] << " ";
			QColor col = QColor(data[i]);
			//std::cout << col.black () << " ";
		}
	}
*/

	if (mDrawBuffer.size()<1) return;

	p.begin (inputImg);
	QPen penB(Qt::black);
	penB.setCapStyle(Qt::RoundCap);
	// ширина кисти в пикселях
	penB.setWidth(4);
	p.setPen(penB);
	//на случай рисования линиями
	//QPainter painter(this);
	//painter.setPen(penB);
	//painter.setCompositionMode(QPainter::CompositionMode_Clear);
	QList<QPoint>::const_iterator it = mDrawBuffer.begin();
	//QPoint start = *it;
	//it++;
	//QList<QPoint>::const_iterator it2 = mDrawBuffer.end();
	//QPoint end = *it2;
	//painter.drawLine(start,start);

	while(it != mDrawBuffer.end()) {
		QPoint end = *it;
		end.setX(end.rx()-12);
		end.setY(end.ry()-26);
		//start = end;
		p.drawPoint(end);
		it++;
	}

	imgDisplayLabel = new QLabel("");
	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	/*scrollArea = new QScrollArea();
	scrollArea->setWidget(imgDisplayLabel);
	scrollArea->setMinimumSize(50,50);
	scrollArea->setMaximumSize(512,512);*/
	//gridLayout->addWidget(scrollArea,0,0);
	gridLayout->addWidget (imgDisplayLabel, 0, 0);
	setLayout(gridLayout);
	mDrawBuffer.clear();
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
		event->accept();
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

void FormWid::pressRecognitionButton ()
{
	return;
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
