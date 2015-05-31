#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <vector>
#include <cmath>
#include "math.h"

class Symbol
{
public:
	//Характеристические функции
	void setMapGravity();
	void getMapGravity(std::vector<std::vector<double> >* out);
	int getwidth();

	//TODO: возможность выбирать карту для каждого символа
	//double EqualMapSymbol();

	//TODO: дозакончить фигуру и сделать такое еще раз
	//void BoldSymbol();

	void CreateMapGravity();
	void CalculationGravityCentr();
	void CalculationSecondMoment();
	void CalculationMomentAboutAxis(int alpha);
	void CalculationHistogram();
	void AlignmentHistogramm();

	std::vector<std::vector<int> > getMatrix() const;
	std::vector<std::vector<bool> > getBinMatrix() const;
	double getGravityCentrX() const;
	double getGravityCentrY() const;
	double getSecondMomentY() const;
	double getSecondMomentX() const;
	double getSecondMomentXY() const;
	void getBinMomentAboutAxis(std::vector<double>* out);
	void setBinMomentAboutAxis(double moment);
	int getName() const;
	double* getHistogram();

	Symbol();
	Symbol(std::vector<int>::iterator itListImg, unsigned int width,
		   unsigned int height);
	//TODO: изменить имя на string
	Symbol(std::vector<int>::iterator itList, int nam, int width, int height);
	~Symbol();

private:
	int name;
	double gravityCentrX, gravityCentrY;			//координаты центра тяжести
	std::vector<std::vector<int> > matrix;				//карта символа
	std::vector<std::vector<bool> > binMatrix;
	std::vector<std::vector<double> > matrixGravity;	//карта тяжести
	size_t width, height;
	//TODO: double mainAlpha;			//угол характеризующий момент относительно оси
	std::vector<double> binMomentAboutAxis;				//в бинарном случае
	//TODO: double minMoment;
	double secondMomentY, secondMomentX, secondMomentXY;
	double histogram [256];
};

#endif // NUMBER_H
