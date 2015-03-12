#include "symbol.h"

Symbol::Symbol()
{
}

Symbol::Symbol(std::vector<int>::iterator itListImg, unsigned int width,
			   unsigned int height)
{
	this->width = width;
	this->height = height;
	for (size_t i = 0; i < height; ++i)
	{
		std::vector<int> temp;
		for (size_t j = 0; j < width; ++j, ++itListImg)
			temp.push_back (*itListImg);
		this->matrix.push_back (temp);
	}
	this->gravityCentrX = 0;
	this->gravityCentrY = 0;
}

Symbol::~Symbol()
{

}
double Symbol::getGravityCentrX() const
{
	return gravityCentrX;
}

double Symbol::getGravityCentrY() const
{
	return gravityCentrY;
}

double Symbol::getSecondMomentX() const
{
	return secondMomentX;
}

double Symbol::getSecondMomentXY() const
{
	return secondMomentXY;
}

void Symbol::getBinMomentAboutAxis(std::vector<double> *out)
{
	out->assign (binMomentAboutAxis.begin (), binMomentAboutAxis.end ());
	return;
}

void Symbol::setBinMomentAboutAxis(double moment)
{
	binMomentAboutAxis.push_back(moment);
	return;
}


double Symbol::getSecondMomentY() const
{
	return secondMomentY;
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
					weihgt += this->matrix[i][j];
			}
			temp.push_back (weihgt / (width * height));
		}
		this->matrixGravity.push_back (temp);
	}
	return;
}

void Symbol::getMapGravity (std::vector<std::vector<double> >* out)
{
	out->assign (matrixGravity.begin (), matrixGravity.end ());
	return;
}

void Symbol::CalculationGravityCentr ()
{
	std::vector<double> listY;
	listY.assign (this->matrixGravity.size (), 0);
	std::vector<double> listX;
	listX.assign (this->matrixGravity.at (0).size (), 0);
	for (size_t i = 0; i < matrixGravity.size (); ++i)
		for (size_t j = 0; j < matrixGravity.at (i).size(); ++j)
		{
			listY.at (i) += matrixGravity.at (i).at(j);
			listX.at (j) += matrixGravity.at (i).at(j);
		}
	double sum = 0;
	for (size_t i = 0; i < listY.size (); ++i)
		sum += listY.at (i);
	for (size_t i = 0; i < listY.size (); ++i)
		listY.at (i) /= sum;
	double expectedValue = 0;
	for (size_t i = 0; i < listY.size (); ++i)
		expectedValue += listY.at (i) * (i+1)/7;
	this->gravityCentrY = expectedValue;
	sum = 0;
	for (size_t i = 0; i < listX.size (); ++i)
		sum += listX.at (i);
	for (size_t i = 0; i < listX.size (); ++i)
		listX.at (i) /= sum;
	expectedValue = 0;
	for (size_t i = 0; i < listX.size (); ++i)
		expectedValue += listX.at (i) * (i+1)/7;
	this->gravityCentrX = expectedValue;
	std::cout << gravityCentrX << " " << gravityCentrY << std::endl;
	return;
}

void Symbol::CalculationSecondMoment ()
{
	std::vector<double> listY;
	listY.assign (this->matrixGravity.size (), 0);
	std::vector<double> listX;
	listX.assign (this->matrixGravity.at (0).size (), 0);
	for (size_t i = 0; i < matrixGravity.size (); ++i)
		for (size_t j = 0; j < matrixGravity.at (i).size(); ++j)
		{
			listY.at (i) += matrixGravity.at (i).at(j);
			listX.at (j) += matrixGravity.at (i).at(j);
		}
	double sum = 0;
	for (size_t i = 0; i < listY.size (); ++i)
		sum += listY.at (i);
	for (size_t i = 0; i < listY.size (); ++i)
		listY.at (i) /= sum;
	for (size_t i = 0; i < listX.size (); ++i)
		listX.at (i) /= sum;

	double secondMoment = 0;
	sum = 0;
	for (size_t i = 0; i < listY.size (); ++i)
	{
		secondMoment += pow((listY.at (i) - this->gravityCentrY), 2);
		sum += listY.at (i);
	}
	secondMoment /= sum;
	this->secondMomentY = secondMoment;

	secondMoment = 0;
	sum = 0;
	for (size_t i = 0; i < listX.size (); ++i)
	{
		secondMoment += pow((listX.at (i) - this->gravityCentrX), 2);
		sum += listX.at (i);
	}
	secondMoment /= sum;
	this->secondMomentX = secondMoment;

	secondMoment = 0;
	for (size_t i = 0; i < listX.size (); ++i)
		secondMoment += pow((listX.at (i) - this->gravityCentrX), 2) *
				pow((listY.at (i) - this->gravityCentrY), 2);
	secondMoment /= sum;
	this->secondMomentXY = secondMoment;

	std::cout << secondMomentX << " " << secondMomentY << " "
			  << secondMomentXY << std::endl;
}

void Symbol::CalculationMomentAboutAxis(int alpha)
//alpha - в градусах
{
	int countPoint = 0;
	unsigned long long int sumDiam = 0;
	double y0, x0;
	y0 = this->height / 2;
	x0 = this->width / 2;

	for (size_t i = 0; i < this->matrix.size(); ++i)
		for (size_t j = 0; j < this->matrix.at(i).size(); ++j)
			if (matrix[i][j] > 0)
			{
				++countPoint;
				double c = sqrt(pow((x0 - j), 2) + pow((y0 - i), 2));
				double beta = acos(std::abs(x0 - j) /c);
				double vega = beta - (alpha * M_PI / 180);
				sumDiam += c * std::abs(sin(vega));
			}
	this->binMomentAboutAxis.push_back((sumDiam + 0.0) / countPoint);

	std::cout << "alpha = " << alpha << " "
			  << this->binMomentAboutAxis.at(
					 this->binMomentAboutAxis.size() - 1) << std::endl;
	return;
}
