#include "tmetrics.h"


double Tmetrics::getPresicion() const
{
	return Presicion;
}

void Tmetrics::setPresicion(double value)
{
	Presicion = value;
}

double Tmetrics::getRecall() const
{
	return Recall;
}

void Tmetrics::setRecall(double value)
{
	Recall = value;
}

double Tmetrics::getF1() const
{
	return F1;
}

void Tmetrics::setF1(double value)
{
	F1 = value;
}

void Tmetrics::CalcMetrics(const TLinerModel LM, const TPool &pool, int number)
{
	double TP = 1,
		FP = 1,
		FN = 1;
	for (size_t iterInstance = 0; iterInstance < pool.Pool.size();
		 ++iterInstance)
	{
		bool pred = LM.IsPositive(pool.Pool.at(iterInstance));
		bool target;
		if (pool.Pool.at(iterInstance).getGoal() == number)
			target = true;
		else
			target = false;
		TP += target & pred;
		FP += !target & pred;
		FN += target & !pred;
	}
	this->Presicion = TP / (TP + FP);
	this->Recall = TP / (TP + FN);
	this->F1 = 1 / (((1 / this->Recall) + (1 / this->Presicion)) / 2);
}

void Tmetrics::Test(TLeaner *L, const TPool &learnPool,
						const TPool &testPool, int number)
{
	CalcMetrics(L->Learn(learnPool), testPool, number);
}

Tmetrics::Tmetrics()
{

}

Tmetrics::~Tmetrics()
{

}

