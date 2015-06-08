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
	double Accuracy;
	double Error;
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
	double getAccuracy() const;
	void setAccuracy(double value);
	double getError() const;
	void setError(double value);
};

#endif // TMETRICS_H
