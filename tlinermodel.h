#ifndef TLINERMODEL_H
#define TLINERMODEL_H

#include "tinstance.h"
#include <numeric>

class TLinerModel
{
private:
	double threshold;

public:
	std::vector <double> coefficients;
	double Prediction (const TInstance &inst) const;
	bool IsPositive (const TInstance &inst) const;
	TLinerModel(int size);
	~TLinerModel();
};

#endif // TLINERMODEL_H
