#pragma once
#include <vector>
#include "Point.h"

class pointStorage {

private: 

	int currpos;
	int size;
	double disttot;
	std::vector<point> points;

public:
	pointStorage(int size);
	void add(vtkIdType pid, double dist);
	point getpoint(int id);
	point *iterate();
	void setPos(int pos);
	double getAvgDist();
};