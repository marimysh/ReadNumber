//#include <QApplication>
//#include <QWidget>
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
#include "knn.h"
#include "alglib/linalg.h"

using namespace alglib;

void SplittoInt2(std::string input, std::vector<int>* out,
								  std::string separator)
{
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(separator)) != std::string::npos) {
		token = input.substr(0, pos);
		out->push_back (atoi(token.c_str ()));
		input.erase(0, pos + separator.length());
	}
	out->push_back (atof(token.c_str ()));
	return;
}

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


void PrintToFile(Symbol *imageSymbol)
{
	std::ofstream outputFileH,outputFileMG, outputFileMD;
	outputFileH.open("../factors_histogram.csv", std::ios::app);
	outputFileMG.open("../factors_map_gravity.csv", std::ios::app);
	outputFileMD.open("../factors_M_D.csv", std::ios::app);
	outputFileH << imageSymbol->getName () << ",";
	outputFileMG << imageSymbol->getName () << ",";
	outputFileMD << imageSymbol->getName () << ",";
/*	std::vector<std::vector<int> > matrix = imageSymbol->getMatrix();
	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			outputFile << (matrix.at(i).at(j) / 255.0) << ",";*/
	/*std::vector<std::vector<bool> > hist = imageSymbol->getBinMatrix();
	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			outputFile << hist.at(i).at(j) << ",";*/
	double * histogram = imageSymbol->getHistogram ();
	for (size_t i = 0; i < 256; ++i)
		outputFileH << *(histogram + i) << ",";

	std::vector<std::vector<double> > map;
	imageSymbol->getMapGravity(&map);
	for (size_t i = 0; i < map.size(); ++i)
		for (size_t j = 0; j < map.at(i).size(); ++j)
			outputFileMG << (map.at(i).at(j) / 255.0) << ",";


	outputFileMD << imageSymbol->getGravityCentrX() << ","
			   << imageSymbol->getGravityCentrY() << ","
			   << imageSymbol->getSecondMomentX() / 2.0 << ","
			   << imageSymbol->getSecondMomentY() / 2.0 << ","
			   << imageSymbol->getSecondMomentXY() / 2.0 << ",";
	/*
	std::vector<double> moment;
	imageSymbol->getBinMomentAboutAxis(&moment);
	for (size_t i = 0; i < moment.size(); ++i)
		outputFile << moment.at(i) << ",";
*/
	outputFileH << std::endl;
	outputFileH.close();
	outputFileMG << std::endl;
	outputFileMG.close();
	outputFileMD << std::endl;
	outputFileMD.close();
	return;
}
void ReadData ()
{
	std::ifstream inputFile;
	inputFile.open ("../train.csv");
	std::string st;
	std::cout << "begin" << std::endl;
	std::getline(inputFile, st);
	QTime timer;
	timer.start ();
	int q = 0;
	while (std::getline(inputFile, st))
	{
		std::cout << q++ << std::endl;
		std::vector<int> listParametrs;
		SplittoInt2 (st, &listParametrs, ",");
		//for (size_t i = 0; i < listParametrs.size (); ++i)
		// std::cout << listParametrs.at (i) << " ";
		//std::cout << std::endl;
		std::vector<int>::iterator begin = listParametrs.begin ();
		begin++;
		Symbol* symbolInp = new Symbol(begin, listParametrs.at (0), 28, 28);
		symbolInp->CalculationHistogram ();
		symbolInp->AlignmentHistogramm ();
		symbolInp->CreateMapGravity ();
		/*std::vector<std::vector<double> > gravCen;
		symbolInp->getMapGravity (&gravCen);
		for (size_t i = 0; i < gravCen.size (); ++i)
		{
			for (size_t j = 0; j < gravCen.at (i).size(); ++j)
				std::cout << gravCen.at (i).at (j) << " ";
			std::cout << std::endl;
		}*/
		symbolInp->CalculationGravityCentr ();
		symbolInp->CalculationSecondMoment ();
/*
		for (size_t alpha = 0; alpha < 180; alpha += 5)
		 symbolInp->CalculationMomentAboutAxis(alpha);*/
		PrintToFile(symbolInp);
		delete symbolInp;
	}
	std::cout << timer.elapsed ();
	inputFile.close ();
	return;
}

int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//FormWid *w = new FormWid();
	//MainWindow w;
	//w->show();

	//ReadData();


	std::string filePath = "../factors_matrix.csv";
//	int razm[] = {100, 200, 400, 500, 700, 1000, 2000, 3000, 4000, 5000, 7000,
//				  10000, 15000, 20000, 30000};
	int razm[] = {1000, 2000, 3000, 4000, 5000, 7000,
				  10000, 15000, 20000, 30000};
	for (size_t sampleSize = 0; sampleSize < 12; ++sampleSize)
	{
		std::cout << "L = " << razm[sampleSize] << std::endl;
		TPool learnp;
		learnp.ReadLearn(filePath, razm[sampleSize]);
		TPool testp;
		testp.ReadTest(filePath, razm[sampleSize], 1000);
/*
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
						 metricsLR.getF1() << " " <<
						 metricsLR.getAccuracy() << " " <<
						 metricsLR.getError() << std::endl;
		}
		std::cout << std::endl;
	}
	*/
		knn MethodKNN(learnp);
		std::cout << MethodKNN.CalcMetrics(testp, 3) << std::endl;
	}
/*
	real_2d_array a = "[[2,1],[1,2]]";
		ae_int_t info;
		matinvreport rep;
		spdmatrixinverse(a, info, rep);
		printf("%d\n", int(info)); // EXPECTED: 1
		printf("%s\n", a.tostring(4).c_str()); // EXPECTED: [[0.666666,-0.333333],[-0.333333,0.666666]]
*/
	return 0;

	//return a.exec();
}
