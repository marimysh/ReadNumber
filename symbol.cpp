#include "symbol.h"

Symbol::Symbol()
{
}

Symbol::Symbol(std::vector<int>::iterator itListImg, int width, int height)
{
	this->width = width;
	this->height = height;
	for (size_t i = 0; i < height; ++i)
	{
		std::vector<int> temp;
		for (size_t j = 0; j < width; ++j, ++itListImg)
			temp.push_back (*itListImg);
		this->Map.push_back (temp);
	}
	this->GravityCentrx = 0;
	this->GravityCentry = 0;
}

Symbol::~Symbol()
{

}

int Symbol::getwidth ()
{
	return this->width;
}

void Symbol::CreateMapGravity ()
{
	int width = this->width / 7;
	int height = this->height / 7;
	for (size_t i7 = 0; i7 < 7; ++i7)
	{
		std::vector<double> temp;
		for (size_t j7 = 0; j7 < 7; ++j7)
		{
			unsigned long long int weihgt = 0;
			for (size_t i = i7*height; i < (i7+1)*height; ++i)
			{
				for (size_t j = j7*width; j < (j7+1)*width; ++j)
					weihgt += this->Map[i][j];
			}
			temp.push_back (weihgt / (width * height));
		}
		this->MapGravity.push_back (temp);
	}
	return;
}

void Symbol::getMapGravity (std::vector<std::vector<double> >* out)
{
	out->assign (MapGravity.begin (), MapGravity.end ());
	return;
}

void Symbol::CalculationGravityCentr ()
{
	std::vector<double> listY;
	listY.assign (this->MapGravity.size (), 0);
	std::vector<double> listX;
	listX.assign (this->MapGravity.at (0).size (), 0);
	for (size_t i = 0; i < MapGravity.size (); ++i)
		for (size_t j = 0; j < MapGravity.at (i).size(); ++j)
		{
			listY.at (i) += MapGravity.at (i).at(j);
			listX.at (j) += MapGravity.at (i).at(j);
		}
	double sum = 0;
	for (size_t i = 0; i < listY.size (); ++i)
		sum += listY.at (i);
	for (size_t i = 0; i < listY.size (); ++i)
		listY.at (i) /= sum;
	double expectedValue = 0;
	for (size_t i = 0; i < listY.size (); ++i)
		expectedValue += listY.at (i) * (i+1)/7;
	this->GravityCentry = expectedValue;
	sum = 0;
	for (size_t i = 0; i < listX.size (); ++i)
		sum += listX.at (i);
	for (size_t i = 0; i < listX.size (); ++i)
		listX.at (i) /= sum;
	expectedValue = 0;
	for (size_t i = 0; i < listX.size (); ++i)
		expectedValue += listX.at (i) * (i+1)/7;
	this->GravityCentrx = expectedValue;
	std::cout << GravityCentrx << " " << GravityCentry << std::endl;
	return;
}
