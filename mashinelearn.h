#ifndef MASHINELEARN_H
#define MASHINELEARN_H

#include <vector>
#include <math.h>

class MashineLearn
{
private:
	std::vector<std::vector<double> > weigt;
	double target;
	double eta;			//magic
public:
	MashineLearn();
	double ThisIsNumber(std::vector<std::vector<double> >::iterator input);
	void LearnKorrectErrors(std::vector<std::vector<double> >::iterator input, double trueAnswer);
	~MashineLearn();
};

#endif // MASHINELEARN_H
