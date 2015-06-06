#ifndef TLINERMODEL_H
#define TLINERMODEL_H

#include "tinstance.h"
#include <numeric>

class TLinerModel
{
private:
	std::vector <double> coefficients;
	double threshold;

public:
	double Prediction (const TInstance &inst) const;
	bool IsPositive (const TInstance &inst) const;
	TLinerModel();
	~TLinerModel();
};

#endif // TLINERMODEL_H
