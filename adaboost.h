#ifndef ADABOOST_H
#define ADABOOST_H

#include "tlinermodel.h"
#include "tpool.h"

class AdaBoost
{
public:
	static TLinerModel Learn (const TPool& pool, int number = -1);
	AdaBoost();
	~AdaBoost();
};

#endif // ADABOOST_H
