#ifndef TINSTANCE_H
#define TINSTANCE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "math.h"
#include "stdlib.h"



class TInstance
{
private:
	int goal;

	void SplittoDouble(std::string input, std::vector<double>* out,
									  std::string separator);
	void SplittoInt2(std::string input, std::vector<int>* out,
									  std::string separator);

public:
	std::vector <double> features;

	void FromString(const std::string st);
	void FromString(int number, const std::string st);
	std::string ToString();
	TInstance();
	~TInstance();
	int getGoal() const;
};

#endif // TINSTANCE_H
