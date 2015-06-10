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
	this->name = -1;
	this->gravityCentrX = 0;
	this->gravityCentrY = 0;
}

Symbol::Symbol(std::vector<int>::iterator itList, int name, int width,
			   int height)
{
	this->width = width;
	this->height = height;
	for (size_t i = 0; i < height; ++i)
	{
		std::vector<int> temp;
		for (size_t j = 0; j < width; ++j, ++itList)
			temp.push_back (*itList);
		this->matrix.push_back (temp);
	}
	this->name = name;
	this->gravityCentrX = 0;
	this->gravityCentrY = 0;
}

Symbol::~Symbol()
{

}
std::vector<std::vector<bool> > Symbol::getBinMatrix() const
{
	return binMatrix;
}

std::vector<std::vector<int> > Symbol::getMatrix() const
{
	return matrix;
}


int Symbol::getName() const
{
	return name;
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
					weihgt += this->matrix.at (i).at (j);
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

double* Symbol::getHistogram ()
{
	return histogram;
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
	//std::cout << gravityCentrX << " " << gravityCentrY << std::endl;
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
			listY.at (i) += matrixGravity.at (i).at (j);
			listX.at (j) += matrixGravity.at (i).at (j);
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

//	std::cout << secondMomentX << " " << secondMomentY << " "
//			  << secondMomentXY << std::endl;
}

void Symbol::CalculationMomentAboutAxis(int alpha)
//alpha - в градусах
{
	int countPoint = 0;
	double sumDiam = 0;
	double y0, x0;
	//y0 = this->height / 2;
	//x0 = this->width / 2;
	y0 = 0.5;
	x0 = 0.5;

	for (size_t i = 0; i < this->binMatrix.size(); ++i)
		for (size_t j = 0; j < this->binMatrix.at(i).size(); ++j)
			if (binMatrix.at (i).at (j) == true)
			{
				++countPoint;
				//double c = sqrt(pow((x0 - j), 2) + pow((y0 - i), 2));
				//double beta = acos(std::abs(x0 - j) /c);
				//double vega = beta - (alpha * M_PI / 180);
				double vega = 90 - alpha;
				double x = j;
				double c = std::abs((x + 0.0)/28.0 - x0);
				sumDiam += c * std::abs(sin(vega * M_PI / 180)) * 4;
			}
	this->binMomentAboutAxis.push_back(sumDiam / (countPoint + 0.0));
	/*std::cout << "alpha = " << alpha << " "
			  << this->binMomentAboutAxis.at (
					 this->binMomentAboutAxis.size() - 1) << std::endl;*/
	return;
}

void Symbol::CalculationHistogram ()
//Метод Оцу
{
	for (size_t i = 0; i < 256; ++i)
		histogram[i] = 0;
	for (size_t i = 0; i < matrix.size (); ++i)
		for (size_t j = 0; j < matrix.at (i).size (); ++j)
			++histogram[matrix.at (i).at (j)];
	unsigned long long int sum = 0;
	for (size_t i = 0; i < 256; ++i)
		sum += histogram[i];
	for (size_t i = 0; i < 256; ++i)
		histogram[i] /= sum;
	int porog = 0;
	double_t minDisp = 1000;
	for (size_t t = 0; t < 256; ++t)
	{
		double_t q1 = 0;
		for (size_t i = 0; i <= t; ++i)
			q1 += histogram[i];
		double_t q2 = 0;
		for (size_t i = t+1; i < 256; ++i)
			q2 += histogram[i];
		double_t u1 = 0;
		for (size_t i = 0; i <= t; ++i)
			u1 += histogram[i] * i / q1;
		double_t u2 = 0;
		for (size_t i = t+1; i < 256; ++i)
			u2 += histogram[i] * i / q2;
		double_t disp1 = 0;
		for (size_t i = 0; i <= t; ++i)
			disp1 += pow((i - u1), 2) * histogram[i] / q1;
		double_t disp2 = 0;
		for (size_t i = t+1; i < 256; ++i)
			disp2 += pow((i - u2), 2) * histogram[i] / q2;
		double_t disp = q1 * disp1 + q2 * disp2;
		if (disp < minDisp)
		{
			minDisp = disp;
			porog = t;
		}
	}
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		std::vector<bool> temp;
		for (size_t j = 0; j < matrix.at (i).size(); ++j)
			if (matrix.at (i). at(j) <= porog)
				temp.push_back (false);
			else
				temp.push_back (true);
		binMatrix.push_back (temp);
	}
	/*for (size_t i = 0; i < binMatrix.size (); ++i)
	{
		for (size_t j = 0; j < binMatrix.at (i). size(); ++j)
			std::cout << binMatrix.at (i). at(j);
		std::cout << std::endl;
	}*/
	return;
}

void Symbol::AlignmentHistogramm ()
{
	for (size_t i = 1; i < 256; ++i)
		histogram[i] += histogram[i-1];
	for (size_t i = 0; i < matrix.size(); ++i)
		for (size_t j = 0; j < matrix.at (i). size(); ++j)
			matrix.at (i). at (j) = round (255 *
										   histogram[matrix.at (i).at (j)]);
	/*for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.at (i). size(); ++j)
			std::cout << matrix.at (i).at (j) << " ";
		std::cout << std::endl;
	}*/
}
