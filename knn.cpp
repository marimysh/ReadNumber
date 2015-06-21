#include "knn.h"

double knn::MetricEvklid(TInstance point1, TInstance point2)
{
	double distance = 0;
	for (size_t i = 0; i < point1.features.size(); ++i)
		distance += pow(point1.features.at(i) - point2.features.at(i), 2);
	return sqrt(distance);
}

std::vector <std::vector<double> > knn::XTX (std::vector<double> v)
{
	std::vector <std::vector<double> > result (v.size(),

											   std::vector <double> (v.size()));
	for (size_t i = 0; i < v.size (); ++i)
		for (size_t j = i; j < v.size (); ++j)
		{
			double value = v.at(i) * v.at(j);
			result.at(i).at(j) = value;
			result.at(j).at(i) = value;
		}
	return result;
}

std::vector <std::vector<double> > MultiMatrix
(std::vector<std::vector<double> > v1,
 std::vector<std::vector<double> > v2)
{
	std::vector <std::vector<double> > result (
				v1.at(0).size(), std::vector<double> (v2.size()));

	//std::cout << v1.size() << " " << v1.at(0).size() << std::endl;
	//std::cout << v2.size() << " " << v2.at(0).size() << std::endl;
	for (size_t i = 0; i < v1.at(0).size (); ++i)
		for (size_t j = 0; j < v2.size (); ++j)
		{
			double value = 0;
			for (size_t k = 0; k < v1.size(); ++k)
				value += v1.at (k).at (i) * v2.at (j).at (k);
			result.at(i).at(j) = value;
		}
	return result;
}

double knn::MetricMakhalanobisa(TInstance point1, TInstance point2)
{
	std::vector<std::vector<double> > S;
	std::vector<double> X;
	X = point1.features;
	double mo = 0;
	for (size_t i = 0; i < point2.features.size (); ++i)
		mo += point2.features.at(i);
	mo /= point2.features.size ();

	for (size_t i = 0; i < X.size(); ++i)
		X.at(i) -= mo;
	S = XTX(X);
	for (size_t i = 0; i < S.size(); ++i)
		for (size_t j = i; j < S.at(0).size(); ++j)
		{
			S.at(i).at(j) *= 1.0 / (X.size() - 1.0);
			S.at(i).at(j) = S.at(j).at(i);
		}

	real_2d_array S1;
	S1.setlength(S.size(), S.at(0).size());
	for (size_t i = 0; i < S.size(); ++i)
		for (size_t j = 0; j < S.at(0).size(); ++j)
			S1(i,j) = S.at(i).at(j);
	ae_int_t info;
	matinvreport rep;
	spdmatrixinverse(S1, info, rep);
	for (size_t i = 0; i < S.size(); ++i)
		for (size_t j = 0; j < S.at(0).size(); ++j)
			S.at(i).at(j) = S1(i,j);

	std::vector<std::vector <double> > vT, v;
	for (size_t i = 0; i < X.size(); ++i)
	{
		std::vector<double> temp;
		temp.push_back(X.at(i));
		vT.push_back(temp);
	}
	v.push_back(X);
	std::vector<std::vector <double> > D = MultiMatrix(MultiMatrix(vT, S), v);
	//std::cout << D.size() << " " << D.at(0).size() << std::endl;
	return sqrt(D.at(0).at(0));
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

double knn::getTP(int i)
{
	return TPm[i];
}

double knn::getFP(int i)
{
	return FPm[i];
}

double knn::getFN(int i)
{
	return FNm[i];
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
	for (int i = 0; i < 10; ++i)
	{
		this->TPm[i] = 0;
		this->FNm[i] = 0;
		this->FPm[i] = 0;
	}
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
	//std::cout << Prediction << " " << input.getGoal() << std::endl;
	if (Prediction == input.getGoal())
		return true;
	else
		return false;
}

void knn::CalcMetrics(TPool test, int countNeighbors)
{
	double truly = 0;
	for (size_t itPool = 0; itPool < test.Pool.size(); ++itPool)
	{
		//if (itPool % 100 == 0)
		//	std::cout << itPool << std::endl;
		bool pred = this->isPositive(test.Pool.at(itPool), countNeighbors);
		for (int i = 0; i < 10; ++i)
		{
			bool target;
			if (test.Pool.at(itPool).getGoal() == i)
				target = true;
			else
				target = false;
			TPm[i] += target & pred;
			FPm[i] += !target & pred;
			FNm[i] += target & !pred;
		}
	}
	return;
}

