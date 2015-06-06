#include "tlinermodel.h"

double TLinerModel::Prediction(const TInstance &inst) const
{
	return std::inner_product(inst.features.begin(), inst.features.end(),
							  this->coefficients.begin(), 0.0);
}

bool TLinerModel::IsPositive(const TInstance &inst) const
{
	return Prediction(inst) > 0;
}

TLinerModel::TLinerModel()
{

}

TLinerModel::~TLinerModel()
{

}

