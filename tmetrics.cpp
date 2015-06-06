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

void Tmetrics::CalcMetrics(const TLinerModel LM, const TPool &pool)
{
	int TP = 0,
		FP = 0,
		FN = 0;
	for (size_t iterInstance = 0; iterInstance < pool.Pool.size();
		 ++iterInstance)
	{
		bool pred = LM.IsPositive(pool.Pool.at(iterInstance));
		bool target = pool.Pool.at(iterInstance).getGoal();
		TP += target & pred;
		FP += !target & pred;
		FN += target & !pred;
	}
	this->Presicion = TP / (TP + FP);
	this->Recall = TP / (TP + FN);
	this->F1 = 1 / (((1 / this->Recall) + (1 / this->Presicion)) / 2);
}

void Tmetrics::Test(TLeaner *L, const TPool &learnPool,
						const TPool &testPool)
{
	CalcMetrics(L->Learn(learnPool), testPool);
}

Tmetrics::Tmetrics()
{

}

Tmetrics::~Tmetrics()
{

}

