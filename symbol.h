#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <vector>

class Symbol
{
public:
	//Характеристические функции
	char whichSymbol();
	void setMapGravity();
	std::vector<std::vector<double> > getMapGravity();
	double getGravityCentrx();
	double getGravityCentry();
	int getwidth();

	//TODO: возможность выбирать карту для каждого символа
	//double EqualMapSymbol();

	//TODO: дозакончить фигуру и сделать такое еще раз
	//void BoldSymbol();

	Symbol();

	Symbol(std::vector<int>::iterator itListImg, int width, int height);
	~Symbol();

private:
	double GravityCentrx, GravityCentry;			//координаты центра тяжести
	std::vector<std::vector<int> > Map;				//карта символа
	std::vector<std::vector<double> > MapGravity;	//карта тяжести
	size_t width, height;
};

#endif // NUMBER_H
