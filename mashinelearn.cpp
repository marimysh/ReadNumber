#include "mashinelearn.h"

MashineLearn::MashineLearn()
{
	this->weight.resize (28,0);
	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			this->weight[i][j] = 0;
	target = 0;
	eta = 1;
}

double MashineLearn::Pmiss (bool y, std::vector<double>::iterator input)
{
	double sum = 0;
	for (size_t i = 0; i < input.size(); ++i)
		sum += input.at(i) * this.weight.at(i);
	if (y)
		return (exp(-sum) / (1 + exp(-sum)));
	else
		return (exp(sum) / (1 + exp(sum)));
}

void MashineLearn::LogicRegression(std::vector<double>::iterator input)
{
	for (size_t i = 0; i < input.size(); ++i)
	{
		int number = input.at(0);
		++input;
		double Ptrue = Pmiss(true, input);
		double Pfalse = Pmiss(false, input);
		for (size_t j = 0; j < 10; ++j)
			if (i == number)
				this.weight.at(j).at(i) += Pmiss(y, input);
	}
}

MashineLearn::~MashineLearn()
{

}

double MashineLearn::ThisIsNumber (std::vector<double>::iterator input)
{
	
}

void MashineLearn::LearnKorrectErrors (std::vector<std::vector<double> >::iterator input,
									   double trueAnswer)
{
	double answer = ThisIsNumber (input);
	if (answer != trueAnswer)
	{
		int e = trueAnswer - answer;
		//double E = pow(e, 2) / 2;
		for (size_t i = 0; i < 28*28; ++i)
		{
//			double_t deltaWeigt = eta*e*input;
//			weigt.at(i) = weigt.at (i) + deltaWeigt;
		}
	}
	return;
}
