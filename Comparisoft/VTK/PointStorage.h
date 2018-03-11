#pragma once
#include <vector>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include "Point.h"

class pointStorage {

private: 

	int currpos;
	int size;
	double disttot;
	std::vector<point> points;

public:
	pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target);
	void add(vtkIdType pid, double dist);
	point getpoint(int id);
	point *iterate();
	double getAvgDist();
};