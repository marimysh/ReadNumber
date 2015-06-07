#include "linerregress.h"

double LinerRegress::sigma(double P, int truly)
{
	return 1 / (1 + exp(truly * P));
}

TLinerModel LinerRegress::Learn(const TPool &pool, int number)
{
	TLinerModel res(pool.Pool.at(0).features.size());
	for (size_t i = 0; i < pool.Pool.size(); ++i)
	{
		double sum = res.Prediction(pool.Pool.at(i));
		int truly;
		if (number == pool.Pool.at(i).getGoal())
			truly = 1;
		else
			truly = -1;
		double P = sigma(sum, truly);
//		std::cout << i << " P " << P << std::endl;
		for (size_t j = 0; j < res.coefficients.size(); ++j)
			res.coefficients[j] += P * truly *
					pool.Pool.at(i).features.at(j);
	}

	return res;
}

LinerRegress::LinerRegress()
{

}

LinerRegress::~LinerRegress()
{

}

