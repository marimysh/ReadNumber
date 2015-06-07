#include <QApplication>
#include <QWidget>
#include "formwid.h"
#include "symbol.h"
#include "machinelearning.h"
#include "tinstance.h"
#include <string.h>
#include <iostream>
#include "tpool.h"
#include "tlinermodel.h"
#include "linerregress.h"
#include "tmetrics.h"

void SplittoDouble(std::string input, std::vector<double>* out,
				   std::string separator)
{
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(separator)) != std::string::npos) {
		token = input.substr(0, pos);
		out->push_back (atof(token.c_str ()));
		input.erase(0, pos + separator.length());
	}
	out->push_back (atof(token.c_str ()));
	return;
}

int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//FormWid *w = new FormWid();
	//MainWindow w;
	//w->show();
/*
	std::ifstream inputFile;
	inputFile.open ("../train.csv");
	std::ofstream outputFile;
	outputFile.open("../factors_map_true.csv", std::ios::app);

	std::string st;
	std::cout << "begin" << std::endl;
	std::getline(inputFile, st);

	QTime timer;
	timer.start ();
	int q = 0;
	while (std::getline(inputFile, st))
	{
		std::cout << ++q << std::endl;
		std::vector<double> listParametrs;
		SplittoDouble (st, &listParametrs, ",");
		outputFile << listParametrs.at(0) << ",";
		for (int i = 1; i < listParametrs.size(); ++i)
			outputFile << listParametrs.at(i) / 255 << ",";
		outputFile << std::endl;
	}

*/
	std::string filePath = "../factors_map_true.csv";
	TPool learnp;
	learnp.ReadLearn(filePath, 1000);
	TPool testp;
	testp.ReadTest(filePath, 1000, 5000);

	std::vector<TLinerModel> weight;
	for (size_t i = 0; i < 10; ++i)
	{
		TLinerModel LG = LinerRegress::Learn(learnp, i);
		weight.push_back(LG);
	}

	for (size_t i = 0; i < 10; ++i)
	{
		Tmetrics metricsLR;
		metricsLR.CalcMetrics(weight.at(i), testp, i);
		std::cout << i << ": ";
		std::cout << metricsLR.getPresicion() << " " <<
					 metricsLR.getRecall() << " " <<
					 metricsLR.getF1() << std::endl;
	}

	return 0;

	//return a.exec();
}
