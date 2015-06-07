#ifndef LINERREGRESS_H
#define LINERREGRESS_H

#include "tleaner.h"

class LinerRegress
{
private:
	static double sigma (double P, int truly);
public:
	static TLinerModel Learn (const TPool& pool, int number = -1);
	LinerRegress();
	~LinerRegress();
};

#endif // LINERREGRESS_H
