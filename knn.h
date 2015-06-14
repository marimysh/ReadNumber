#ifndef KNN_H
#define KNN_H

#include "tpool.h"
#include <utility>
#include <map>

class knn
{
private:
	double MetricEvklid (TInstance point1, TInstance point2);
	void DeleteFarthestNeighbors();
	std::vector <std::pair <TInstance, double> > favourite;
	void ReloadMaxFar();
	TPool pooltrain;
	double maxFar;
	double TP;
	double FP;
	double FN;
public:
	knn(TPool train);
	~knn();
	int Model (TInstance input, int countNeighbors);
	bool isPositive(TInstance input, int countNeighbors);
	double CalcMetrics(TPool test, int countNeighbors);
	double getTP() const;
	double getFP() const;
	double getFN() const;
};

#endif // KNN_H
