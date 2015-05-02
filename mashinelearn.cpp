#include "mashinelearn.h"

MashineLearn::MashineLearn()
{
	//this->weigt.resize (28,0);
	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			this->weigt[i][j] = 0;
	target = 0;
	eta = 1;
}

MashineLearn::~MashineLearn()
{

}

double MashineLearn::ThisIsNumber (std::vector<std::vector<double> >::iterator input)
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
