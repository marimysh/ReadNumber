#ifndef KNN_H
#define KNN_H

#include "tpool.h"
#include <utility>
#include <map>
#include <algorithm>
#include "alglib/linalg.h"

using namespace alglib;

class knn
{
private:
	double MetricEvklid (TInstance point1, TInstance point2);
	void DeleteFarthestNeighbors();
	std::vector <std::vector<double> > XTX (std::vector<double> v);
	double MetricMakhalanobisa(TInstance point1, TInstance point2);
	std::vector <std::pair <TInstance, double> > favourite;
	void ReloadMaxFar();
	TPool pooltrain;
	double maxFar;
	double TP;
	double FP;
	double FN;
	double TPm [10], FPm[10], FNm[10];
public:
	knn(TPool train);
	~knn();
	int Model (TInstance input, int countNeighbors);
	bool isPositive(TInstance input, int countNeighbors);
	void CalcMetrics(TPool test, int countNeighbors);
	double getTP() const;
	double getFP() const;
	double getFN() const;
	double getTP(int i);
	double getFP(int i);
	double getFN(int i);
};

#endif // KNN_H
