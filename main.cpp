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
	std::string namefile = "matrix_3";
//	int razm[] = {100, 500, 700, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 7000,
//				  10000, 12500, 15000, 17500, 20000, 25000, 30000};
	int razm[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 7000,
	10000, 15000, 20000, 30000};
	int countrazm = 12;

	double metricsForNumber[countrazm][10][5];
	for (size_t l = 0; l < countrazm; ++l)
	for (int j = 0; j < 10; ++j)
		for (int k = 0; k < 5; ++k)
			metricsForNumber[l][j][k] = 0;

	for (size_t sampleSize = 0; sampleSize < countrazm; ++sampleSize)
	{
		std::cout << razm[sampleSize] << std::endl;
		TPool learnp;
		learnp.ReadLearn(filePath, razm[sampleSize]);
		TPool testp;
		testp.ReadTest(filePath, razm[sampleSize], 2000);
/*
		std::vector<TLinerModel> weight;
		for (size_t i = 0; i < 10; ++i)
		{
			TLinerModel LG = LinerRegress::Learn(learnp, i);
			weight.push_back(LG);
		}

		for (int j = 0; j < 10; ++j)
		{
			Tmetrics metricsLR;
			metricsLR.CalcMetrics(weight.at(j), testp, j);

			metricsForNumber[sampleSize][j][0] = metricsLR.getPresicion();
			metricsForNumber[sampleSize][j][1] = metricsLR.getRecall();
			metricsForNumber[sampleSize][j][2] = metricsLR.getF1();
			metricsForNumber[sampleSize][j][3] = metricsLR.getAccuracy();
			metricsForNumber[sampleSize][j][4] = metricsLR.getError();
		}
*/
		knn MethodKNN(learnp);
		MethodKNN.CalcMetrics(testp, 3);
		for (int j = 0; j < 10; ++j)
		{
			Tmetrics metricsLR;
			metricsLR.CalcMetricsValue(2000, MethodKNN.getTP(j),
									   MethodKNN.getFP(j), MethodKNN.getFN(j));
			metricsForNumber[sampleSize][j][0] = metricsLR.getPresicion();
			metricsForNumber[sampleSize][j][1] = metricsLR.getRecall();
			metricsForNumber[sampleSize][j][2] = metricsLR.getF1();
			metricsForNumber[sampleSize][j][3] = metricsLR.getAccuracy();
			metricsForNumber[sampleSize][j][4] = metricsLR.getError();
		}

	}

	std::ofstream outputFile1;
	outputFile1.open ("../graphs/KNN/Presision_" + namefile + ".txt");
	std::ofstream outputFile2;
	outputFile2.open ("../graphs/KNN/Recall_" + namefile + ".txt");
	std::ofstream outputFile3;
	outputFile3.open ("../graphs/KNN/F1_" + namefile + ".txt");
	std::ofstream outputFile4;
	outputFile4.open ("../graphs/KNN/Accuracy_" + namefile + ".txt");
	std::ofstream outputFile5;
	outputFile5.open ("../graphs/KNN/Error_" + namefile + ".txt");

	for (int i = 0; i < countrazm; ++i)
	{
		outputFile1 << razm[i] << " ";
		outputFile2 << razm[i] << " ";
		outputFile3 << razm[i] << " ";
		outputFile4 << razm[i] << " ";
		outputFile5 << razm[i] << " ";

		for (int j = 0; j < 10; ++j)
		{
			outputFile1 << metricsForNumber[i][j][0] << " ";
			outputFile2 << metricsForNumber[i][j][1] << " ";
			outputFile3 << metricsForNumber[i][j][2] << " ";
			outputFile4 << metricsForNumber[i][j][3] << " ";
			outputFile5 << metricsForNumber[i][j][4] << " ";
		}
		outputFile1 << std::endl;
		outputFile2 << std::endl;
		outputFile3 << std::endl;
		outputFile4 << std::endl;
		outputFile5 << std::endl;
	}
	outputFile1.close();
	outputFile2.close();
	outputFile3.close();
	outputFile4.close();
	outputFile5.close();

	outputFile1.open ("../graphs/KNN/av_" + namefile + ".txt");

	for (int i = 0; i < countrazm; ++i)
	{
		outputFile1 << razm[i] << " ";

		double av1 = 0;
		double av2 = 0;
		double av3 = 0;
		double av4 = 0;
		double av5 = 0;

		for (int j = 0; j < 10; ++j)
		{
			av1 += metricsForNumber[i][j][0];
			av2 += metricsForNumber[i][j][1];
			av3 += metricsForNumber[i][j][2];
			av4 += metricsForNumber[i][j][3];
			av5 += metricsForNumber[i][j][4];
		}
		av1 /= 10;
		av2 /= 10;
		av3 /= 10;
		av4 /= 10;
		av5 /= 10;
		outputFile1 << av1 << " " << av2 << " " << av3 << " " << av4 << " "
						<< av5;
		outputFile1 << std::endl;
	}
	outputFile1.close();
	return 0;

	//return a.exec();
}
