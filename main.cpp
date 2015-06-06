#include <QApplication>
#include <QWidget>
#include "formwid.h"
#include "symbol.h"
#include "machinelearning.h"
#include "tinstance.h"
#include <string.h>

/*
void PrintToFile(Symbol *imageSymbol)
{
	std::ofstream outputFile;
	outputFile.open("../factors_GC_GM_3.csv", std::ios::app);

	outputFile << imageSymbol->getName () << ",";

/*	std::vector<std::vector<int> > matrix = imageSymbol->getMatrix();

	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			outputFile << matrix.at(i).at(j) << ",";

	std::vector<std::vector<bool> > hist = imageSymbol->getBinMatrix();
	for (size_t i = 0; i < 28; ++i)
		for (size_t j = 0; j < 28; ++j)
			outputFile << hist.at(i).at(j) << ",";

	double * histogram = imageSymbol->getHistogram ();
	for (size_t i = 0; i < 256; ++i)
		outputFile << *(histogram + i) << ",";

	std::vector<std::vector<double> > map;
	imageSymbol->getMapGravity(&map);
	for (size_t i = 0; i < map.size(); ++i)
		for (size_t j = 0; j < map.at(i).size(); ++j)
			outputFile << map.at(i).at(j) << ",";
*/
/*	outputFile << imageSymbol->getGravityCentrX() << ","
			   << imageSymbol->getGravityCentrY() << ","
			   << imageSymbol->getSecondMomentX() << ","
			   << imageSymbol->getSecondMomentY() << ","
			   << imageSymbol->getSecondMomentXY() << ",";
/*
	std::vector<double> moment;
	imageSymbol->getBinMomentAboutAxis(&moment);
	for (size_t i = 0; i < moment.size(); ++i)
		outputFile << moment.at(i) << ",";

	outputFile << std::endl;
	outputFile.close();
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
		//	std::cout << listParametrs.at (i) << " ";
		//std::cout << std::endl;

		std::vector<int>::iterator begin = listParametrs.begin ();
		begin++;
		Symbol* symbolInp = new Symbol(begin, listParametrs.at (0), 28, 28);
		symbolInp->CalculationHistogram ();
		//symbolInp->AlignmentHistogramm ();

		symbolInp->CreateMapGravity ();
		//std::vector<std::vector<double> > gravCen;
		//symbolInp->getMapGravity (&gravCen);
		//for (size_t i = 0; i < gravCen.size (); ++i)
		//{
		//	for (size_t j = 0; j < gravCen.at (i).size(); ++j)
		//		std::cout << gravCen.at (i).at (j) << " ";
		//	std::cout << std::endl;
		//}

		symbolInp->CalculationGravityCentr ();
		symbolInp->CalculationSecondMoment ();
		//for (size_t alpha = 0; alpha < 180; alpha += 4)
		//	symbolInp->CalculationMomentAboutAxis(alpha);
		PrintToFile(symbolInp);
		delete symbolInp;
	}
	std::cout << timer.elapsed ();
	inputFile.close ();
	return;
}

void LearnLG ()
{
	std::ifstream inputFile;
	inputFile.open ("../factors_bin_map_GC_GM.csv");

	std::string st;
	std::cout << "begin" << std::endl;

	std::ofstream outputFile;
	outputFile.open("../weight_bin_map_GC_GM.csv", std::ios::app);
	std::vector<double> listParametrs;
	QTime timer;
	timer.start ();
	int q = 0;
//	std::getline(inputFile, st);
	std::getline(inputFile, st);
	SplittoDouble (st, &listParametrs, ",");
	MachineLearning* LG = new MachineLearning(listParametrs.size() - 1);
	LG->LogicRegression(listParametrs.begin(), listParametrs.end());

	while (std::getline(inputFile, st) && (q < 10))
	{
		std::cout << q++ << std::endl;
		listParametrs.clear();
		SplittoDouble (st, &listParametrs, ",");
//		std::cout << listParametrs.size() << std::endl;
		LG->LogicRegression(listParametrs.begin(), listParametrs.end());
	}

	std::vector<std::vector<double> > weightres = LG->getWeight();
	for (size_t j = 0; j < 10; ++j)
	{
		//outputFile << j << ",";
		for (size_t i = 0; i < weightres.at(0).size(); ++i)
			outputFile << weightres.at(j).at(i) << ",";
		outputFile << std::endl;
	}
	std::cout << timer.elapsed ();
	outputFile.close();
	return;
}

void CheckLearning ()
{
	std::ifstream inputFile;
	inputFile.open ("../weight_GC_GM.csv");

	std::string st;
	std::cout << "begin" << std::endl;

	std::vector<double> listParametrs;
	QTime timer;
	timer.start ();
	int q = 0;

	std::vector<std::vector<double> > weight;

	while (std::getline(inputFile, st))
	{
		SplittoDouble (st, &listParametrs, ",");
		weight.push_back(listParametrs);
		listParametrs.clear();
	}
	std::cout << weight.at(0).size() << std::endl;
	inputFile.close();

	inputFile.open ("../train.csv");
	while (std::getline(inputFile, st) && (q < 1000))
		++q;
	std::vector<int> listParametrsinp;

	int truly[10][2];
	for (size_t i = 0; i < 10; ++i)
	{
		truly[i][0] = 0;
		truly[i][1] = 0;
	}

	while (std::getline(inputFile, st) && (q < 2000))
	{
		std::cout << q++ << std::endl;
		SplittoInt2 (st, &listParametrsinp, ",");
		std::vector<int>::iterator begin = listParametrsinp.begin ();
		int name = *begin++;

		Symbol* symbolInp = new Symbol(begin, name, 28, 28);
		symbolInp->CalculationHistogram ();

		symbolInp->CreateMapGravity ();

		symbolInp->CalculationGravityCentr ();
		//symbolInp->CalculationSecondMoment ();

		double myints[] = {symbolInp->getGravityCentrX(),
						   symbolInp->getGravityCentrY(),
						   symbolInp->getSecondMomentX(),
						   symbolInp->getSecondMomentY(),
						   symbolInp->getSecondMomentXY()};

		std::vector<double> listGC (myints,
									myints + sizeof(myints) / sizeof(double) );
		long long sum = 0, max = -5;
		int maxnumber = -1;

		std::cout << symbolInp->getName() << " ";
		for (size_t j = 0; j < 10; ++j)
		{
			sum = 0;
			for (size_t i = 0; i < listGC.size(); ++i)
				sum += weight.at(j).at(i) * listGC.at(i);
			sum += 5;
			//std::cout << weight.at(j).at(0) << " ";
			std::cout << 1/(1 + exp(-sum)) << " ";
			if (1/(1 + exp(-sum)) > max)
			{
				maxnumber = j;
				max = 1/(1 + exp(-sum));
			}
		}
		std::cout << std::endl;

		if (symbolInp->getName() == maxnumber)
			truly[symbolInp->getName()][0]++;
		else
			truly[symbolInp->getName()][1]++;
		delete symbolInp;
		listParametrsinp.clear();
	}
	for (size_t i = 0; i < 10; ++i)
		std::cout << i << " " << truly[i][0] << " " << truly[i][1] << std::endl;
}

void Kost ()
{
	std::ifstream inputFile;
	inputFile.open ("../factors_GC_GM.csv");

	std::string st;
	std::cout << "begin" << std::endl;

	std::ofstream outputFile;
	outputFile.open("../factors_GC_GM_2.csv", std::ios::app);

	std::vector<double> listParametrs;

	while (std::getline(inputFile, st))
	{
		listParametrs.clear();
		SplittoDouble (st, &listParametrs, ",");
		bool fl = true;
		for (size_t i = 0; i < listParametrs.size(); ++i)
			if (listParametrs.at(i) > 100)
			{
				fl = false;
				std::cout << listParametrs.at(i) << std::endl;
				i = listParametrs.size();
			}
		if (fl) {
			for (size_t i = 0; i < listParametrs.size(); ++i)
				outputFile << listParametrs.at(i) << ",";
			outputFile << std::endl;
		}
	}
	return;
}
*/
int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//FormWid *w = new FormWid();

	//MainWindow w;
	//w->show();
	//ReadData();
	//Kost();
	//LearnLG();
	//CheckLearning();


	//TInstance TI;
	return 0;
	//return a.exec();
}
