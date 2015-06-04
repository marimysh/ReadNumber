#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include <iostream>
#include <vector>
#include <math.h>

class MachineLearning
{
private:
	std::vector<std::vector<long long int> > weight;
	double target;
	double eta;			//magic

	double Pmiss (bool y, std::vector<double>::iterator input,
				  std::vector<double>::iterator inputend, int number);

public:
	MachineLearning();
	MachineLearning(int size);
	double ThisIsNumber(std::vector<double>::iterator input);
	void LearnKorrectErrors(std::vector<double>::iterator input,
							double trueAnswer);
	void LogicRegression(std::vector<double>::iterator input,
						 std::vector<double>::iterator inputend);
	~MachineLearning();

	std::vector<std::vector<long long> > getWeight() const;
};

#endif // MACHINELEARNING_H
