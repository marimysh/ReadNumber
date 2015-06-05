#ifndef TLINERMODEL_H
#define TLINERMODEL_H

#include <vector>
#include "tinstance.h"

class TLinerModel
{
private:
	std::vector <double> Coefficients;
	double Threshold;

public:
	double Prediction (const TInstance &inst) const;
	bool IsPositive (const TInstance &inst) const;
	TLinerModel();
	~TLinerModel();
};

#endif // TLINERMODEL_H
