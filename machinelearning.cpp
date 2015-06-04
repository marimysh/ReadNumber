#include "machinelearning.h"

MachineLearning::MachineLearning(int size)
{
	this->weight.resize (10, std::vector<long long int> (size, 0.00001));
	std::cout << weight.size() << " " << weight.at(0).size() << std::endl;
/*	for (size_t i = 0; i < 10; ++i)
	{
		std::vector<double> temp;
		for (size_t j = 0; j < size; ++j)
			temp.push_back (0);
		this->weight.push_back (temp);
	}*/
	target = 0;
	eta = 1;
}

MachineLearning::MachineLearning()
{
	//this->weigt.resize (28,0);
	target = 0;
	eta = 1;
}

MachineLearning::~MachineLearning()
{

}


std::vector<std::vector<long long int> > MachineLearning::getWeight() const
{
	return weight;
}

double MachineLearning::ThisIsNumber (std::vector<double>::iterator input)
{
	
}

void MachineLearning::LearnKorrectErrors (std::vector<double>::iterator input,
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
//			weight.at(i) = weight.at (i) + deltaWeigt;
		}
	}
	return;
}

double MachineLearning::Pmiss (bool y, std::vector<double>::iterator input,
							   std::vector<double>::iterator inputend,
							   int number)
{
	long long int sum = 5;
	for (size_t i = 0; input < inputend; ++i, ++input) {
//		std::cout << *input << " " << this->weight.at(number).at(i) << std::endl;
		sum += *input *	this->weight.at(number).at(i);
	}
	std::cout << "S " << sum << " ";
	if (y)
		return (exp(-sum) / (1 + exp(-sum)));
	else
		return (exp(sum) / (1 + exp(sum)));
}

void MachineLearning::LogicRegression(std::vector<double>::iterator input,
									  std::vector<double>::iterator inputend)
{
		int number = *input++;
		for (size_t j = 0; j < 10; ++j)
		{
			double P;
			std::vector<double>::iterator inp = input;
			if (j == number) {
				P = Pmiss(true, input, inputend, j);
				for (size_t i = 0; inp < inputend; ++i, ++inp)
					this->weight.at(j).at(i) += P * 1 * (*inp);
			}
			else {
				P = Pmiss(false, input, inputend, j);
				for (size_t i = 0; inp < inputend; ++i, ++inp)
					this->weight.at(j).at(i) += P * (-1) * (*inp);
			}
			inp = input;
			for (size_t i = 0; inp < inputend; ++i, ++inp)
				std::cout << this->weight.at(j).at(i) << " ";
			std::cout << "P " << P << std::endl;
		}
		return;
}
