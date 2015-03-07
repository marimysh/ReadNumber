#ifndef FORMWID_H
#define FORMWID_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPainter>
#include <QBrush>
#include <QtCore/QLine>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QPen>
#include <QPushButton>

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

private:
	Ui::FormWid *ui;
	QGridLayout* gridLayout;
	QImage* inputImg;
	QLabel* imgDisplayLabel;
	//QScrollArea* scrollArea;
	QPushButton* recognitionButton;
	QList<QPoint> mDrawBuffer;
	bool mDrawMode;
};

#endif // FORMWID_H