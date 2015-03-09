#ifndef FORMWID_H
#define FORMWID_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPainter>
#include <QBrush>
#include <QtCore/QLine>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QPen>
#include <QPushButton>

#include "iostream"
#include "symbol.h"
#include <vector>

namespace Ui {
class FormWid;
}

class FormWid : public QWidget
{
	Q_OBJECT

public:
	explicit FormWid(QWidget *parent = 0);
	~FormWid();

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void pressRecognitionButton();
	void pressFirstButton();
	void pressTeachButton();

private:
	Ui::FormWid *ui;
	QGridLayout* gridLayout;
	QVBoxLayout* layoutButtons;
	QImage* inputImg;
	QLabel* imgDisplayLabel;
	QPushButton* firstButton;
	QPushButton* recognitionButton;
	QPushButton* teachButton;
	QList<QPoint> mDrawBuffer;
	bool mDrawMode;
};

#endif // FORMWID_H
