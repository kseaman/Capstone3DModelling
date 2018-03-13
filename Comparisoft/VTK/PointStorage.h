#pragma once
#include <vector>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include "Point.h"
using namespace std;

class pointStorage {

private: 

	int sizeS;
	int sizeT;
	double distS;
	double distT;
	vector<point> sourceList;
	vector<point> targetList;
	vtkSmartPointer<vtkPolyData> sourceData;
	vtkSmartPointer<vtkPolyData> targetData;

public:
	pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target);
	void calculateSource();
	void calculateTarget();
	vector<point> sourcePoints();
	vector<point> targetPoints();
	double getAvgSource();
	double getAvgTarget();
};