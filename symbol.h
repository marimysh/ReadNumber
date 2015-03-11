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
	double getGravityCentrx();
	double getGravityCentry();
	int getwidth();

	//TODO: возможность выбирать карту для каждого символа
	//double EqualMapSymbol();

	//TODO: дозакончить фигуру и сделать такое еще раз
	//void BoldSymbol();

	void CreateMapGravity();
	void CalculationGravityCentr();
	void CalculationSecondMoment();
	void CalculationMomentAboutAxis(int alpha);

	Symbol();

	Symbol(std::vector<int>::iterator itListImg, unsigned int width,
		   unsigned int height);
	~Symbol();

private:
	double gravityCentrX, gravityCentrY;			//координаты центра тяжести
	std::vector<std::vector<int> > matrix;				//карта символа
	std::vector<std::vector<double> > matrixGravity;	//карта тяжести
	size_t width, height;
	double mainAlpha;									//угол характеризующий момент относительно оси
	double binMomentAboutAxis;							//в бинарном случае
	double secondMomentY, secondMomentX, secondMomentXY;

};

#endif // NUMBER_H
