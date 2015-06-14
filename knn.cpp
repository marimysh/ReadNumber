#include "knn.h"

double knn::MetricEvklid(TInstance point1, TInstance point2)
{
	double distance = 0;
	for (size_t i = 0; i < point1.features.size(); ++i)
		distance += pow(point1.features.at(i) - point2.features.at(i), 2);
	return sqrt(distance);
}

void knn::DeleteFarthestNeighbors()
{
	for (size_t i = 0; i < favourite.size(); ++i)
		if (favourite.at(i).second == maxFar)
		{
			favourite.erase(favourite.begin() + i);
			return;
		}
	return;
}

void knn::ReloadMaxFar()
{
	this->maxFar = 0;
	for (size_t i = 0; i < this->favourite.size(); ++i)
		if (this->maxFar < this->favourite.at(i).second)
			this->maxFar = this->favourite.at(i).second;
}
double knn::getFN() const
{
	return FN;
}

double knn::getFP() const
{
	return FP;
}

double knn::getTP() const
{
	return TP;
}


knn::knn(TPool train)
{
	this->pooltrain = train;
}

knn::~knn()
{

}

int knn::Model(TInstance input, int countNeighbors)
{
	int res = 0;
	maxFar = 1000;
	favourite.clear();
	favourite.reserve(countNeighbors);

	double d = MetricEvklid(input, pooltrain.Pool.at(0));
	maxFar = d;
	std::pair <TInstance, double> NewN (
				pooltrain.Pool.at(0), d);
	this->favourite.push_back(NewN);

	for (size_t itPool = 0; itPool < this->pooltrain.Pool.size(); ++itPool)
	{
		double distance = MetricEvklid(input, pooltrain.Pool.at(itPool));
		if (distance < maxFar)
		{
			if (this->favourite.size() >= countNeighbors)
				DeleteFarthestNeighbors();
			std::pair <TInstance, double> NewNeighbor (
						pooltrain.Pool.at(itPool), distance);
			this->favourite.push_back(NewNeighbor);
			ReloadMaxFar();
		}
	}

	std::map <int, double> favouriteCount;
	for (size_t itFavourite = 0; itFavourite < this->favourite.size();
		 ++itFavourite)
	{
		if (favouriteCount.find(this->favourite.at(itFavourite).first.getGoal())
				== favouriteCount.end())
			favouriteCount[this->favourite.at(itFavourite).first.getGoal()]
					= 1 / pow(this->favourite.at(itFavourite).second, 2);
		else
			favouriteCount[this->favourite.at(itFavourite).first.getGoal()]
					= favouriteCount[this->favourite.at(itFavourite).first
					.getGoal()]
					+ 1 / pow(this->favourite.at(itFavourite).second, 2);
	}

	if (favouriteCount.size() == 1)
		res = this->favourite.at(0).first.getGoal();
	else
	{
		int max = 0;
		for (std::map<int,double>::iterator it=favouriteCount.begin();
		it != favouriteCount.end(); ++it)
			if (it->second > max)
			{
				max = it->second;
				res = it->first;
			}
	}
	return res;
}

bool knn::isPositive(TInstance input, int countNeighbors)
{
	int Prediction = Model(input, countNeighbors);
	if (Prediction == input.getGoal())
		return true;
	else
		return false;
}

double knn::CalcMetrics(TPool test, int countNeighbors)
{
	double truly = 0;
	for (size_t itPool = 0; itPool < test.Pool.size(); ++itPool)
	{
		//std::cout << itPool << std::endl;
		if (this->isPositive(test.Pool.at(itPool), countNeighbors))
			truly++;
	}
	return truly / test.Pool.size();
}

