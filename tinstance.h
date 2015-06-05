#ifndef TINSTANCE_H
#define TINSTANCE_H

#include <iostream>
#include "string.h"

class TInstance
{
private:
	int Goal;
	std::vector <double> features;
public:
	static TInstance FromString(const std::string st);
	std::string ToString() const;
	TInstance();
	~TInstance();
};

#endif // TINSTANCE_H
