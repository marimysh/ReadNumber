#include "formwid.h"
#include "ui_formwid.h"

FormWid::FormWid(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormWid)
{
	gridLayout = new QGridLayout();
	layoutButtons = new QVBoxLayout();
	inputImg = new QImage("ksh.png");
	imgDisplayLabel = new QLabel("");

	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	gridLayout->addWidget (imgDisplayLabel, 0, 0);

	readButton = new QPushButton("Read data", this);
	connect (readButton, SIGNAL(released()), this,
			 SLOT(pressReadButton()));
	layoutButtons->addWidget (readButton, 0);

	firstButton = new QPushButton("To start again", this);
	connect (firstButton, SIGNAL(released()), this,
			 SLOT(pressFirstButton()));
	layoutButtons->addWidget (firstButton, 1);

	recognitionButton = new QPushButton("Recognition", this);
	connect (recognitionButton, SIGNAL(released()), this,
			 SLOT(pressRecognitionButton()));
	layoutButtons->addWidget (recognitionButton, 2);

	teachButton = new QPushButton("Teaching", this);
	connect (teachButton, SIGNAL(released()), this,
			 SLOT(pressTeachButton()));
	layoutButtons->addWidget (teachButton, 3);

	gridLayout->addLayout (layoutButtons, 0, 2);
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
	delete inputImg;
	return;
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
	unsigned int pixels = inputImg->width() * inputImg->height();
	if (pixels*(int)sizeof(QRgb) <= (unsigned int)inputImg->byteCount())
	{
		QRgb *data = (QRgb *)inputImg->bits();
		std::vector<int> imgPixels;
		for (size_t i = 0; i < pixels; ++i)
		{
			QColor greyCode = QColor(data[i]);
			imgPixels.push_back (greyCode.black ());
		}
		std::vector<int>::iterator begin;
		begin = imgPixels.begin ();
		Symbol* symbolInp = new Symbol(begin, inputImg->width (),
									   inputImg->height ());
		symbolInp->CreateMapGravity ();
		std::vector<std::vector<double> > gravCen;
		symbolInp->getMapGravity (&gravCen);
		for (size_t i = 0; i < gravCen.size (); ++i)
		{
			for (size_t j = 0; j < gravCen.at (i).size(); ++j)
				std::cout << gravCen[i][j] << " ";
			std::cout << std::endl;
		}
		symbolInp->CalculationGravityCentr ();
		symbolInp->CalculationSecondMoment ();
		symbolInp->CalculationMomentAboutAxis(0);
		symbolInp->CalculationMomentAboutAxis(90);
		delete symbolInp;
	}
	return;
}

void FormWid::pressFirstButton ()
{
	delete imgDisplayLabel;
	inputImg = new QImage("ksh.png");
	imgDisplayLabel = new QLabel("");
	imgDisplayLabel->setPixmap(QPixmap::fromImage(*inputImg));
	imgDisplayLabel->adjustSize();
	gridLayout->addWidget (imgDisplayLabel, 0, 0);
	delete inputImg;
	return;
}

void FormWid::pressTeachButton ()
{
	return;
}

void FormWid::pressReadButton ()
{
	return;
}
