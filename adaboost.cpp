#include "adaboost.h"

TLinerModel AdaBoost::Learn(const TPool &pool, int number)
{
	int countFeatures = pool.Pool.at(0).features.size();
	TLinerModel res(countFeatures);

	std::vector<double> D;
	D.assign(countFeatures, 1.0 / countFeatures);



	for (size_t i = 0; i < pool.Pool.size(); ++i)
	{
		double sum = res.Prediction(pool.Pool.at(i));
		int truly;
		if (number == pool.Pool.at(i).getGoal())
			truly = 1;
		else
			truly = -1;
//		double P = sigma(sum, truly);
		double P;
//		std::cout << i << " P " << P << std::endl;
		for (size_t j = 0; j < res.coefficients.size(); ++j)
			res.coefficients[j] += P * truly *
					pool.Pool.at(i).features.at(j);
	}

	return res;
}

AdaBoost::AdaBoost()
{

}

AdaBoost::~AdaBoost()
{

}

