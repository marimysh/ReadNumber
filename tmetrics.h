#ifndef TMETRICS_H
#define TMETRICS_H

#include "tlinermodel.h"
#include "tpool.h"
#include "tleaner.h"

class Tmetrics
{
private:
	double Presicion;
	double Recall;
	double F1;
public:
	Tmetrics();
	~Tmetrics();
	double getPresicion() const;
	void setPresicion(double value);
	double getRecall() const;
	void setRecall(double value);
	double getF1() const;
	void setF1(double value);

	void CalcMetrics (const TLinerModel LM, const TPool &pool, int number);
	void Test (TLeaner *L, const TPool &learnPool, const TPool &testPool,
			   int number);
};

#endif // TMETRICS_H
