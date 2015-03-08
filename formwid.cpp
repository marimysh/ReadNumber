#include "formwid.h"
#include "ui_formwid.h"

FormWid::FormWid(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormWid)
{
	gridLayout = new QGridLayout();
	inputImg = new QImage("ksh.png");
	imgDisplayLabel = new QLabel("");
	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	gridLayout->addWidget (imgDisplayLabel, 0, 0);

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

	if (mDrawBuffer.size()<1) return;

	p.begin (inputImg);
	QPen penB(Qt::black);
	penB.setCapStyle(Qt::RoundCap);
	// ширина кисти в пикселях
	penB.setWidth(4);
	p.setPen(penB);

	QList<QPoint>::const_iterator it = mDrawBuffer.begin();

	while(it != mDrawBuffer.end()) {
		QPoint end = *it;
		end.setX(end.rx()-12);
		end.setY(end.ry()-26);
		p.drawPoint(end);
		it++;
	}

	imgDisplayLabel = new QLabel("");
	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	gridLayout->addWidget (imgDisplayLabel, 0, 0);
	setLayout(gridLayout);
	mDrawBuffer.clear();
	p.end();
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
	int pixels = inputImg->width() * inputImg->height();
	if (pixels*(int)sizeof(QRgb) <= inputImg->byteCount())
	{
		QRgb *data = (QRgb *)inputImg->bits();
		std::vector<int> imgPixels;
		for (size_t i = 0; i < pixels; ++i)
		{

			//data[i] = qRgba(val, val, val, qAlpha(data[i]));
			//std::cout << data[i] << " ";
			QColor greyCode = QColor(data[i]);
			//std::cout << col.black () << " ";
			imgPixels.push_back (greyCode.black ());
		}
		std::vector<int>::iterator begin;
		begin = imgPixels.begin ();
		Symbol* symbolInp = new Symbol(begin, inputImg->width (), inputImg->height ());
		std::cout << symbolInp->getwidth ();
	}
	return;
}
