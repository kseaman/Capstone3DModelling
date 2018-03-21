#pragma once
//#include <vector>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkFloatArray.h>
//#include "Point.h"
using namespace std;

class pointStorage {

private: 

	int sizeS;
	int sizeT;
	double distTotS;
	double distTotT;
	double maxDistS;
	double minDistS;
	double maxDistT;
	double minDistT;
	//vector<point> sourceList;
	//vector<point> targetList;
	vtkSmartPointer<vtkFloatArray> scalarsS;
	vtkSmartPointer<vtkFloatArray> scalarsT;
	vtkSmartPointer<vtkPolyData> sourceData;
	vtkSmartPointer<vtkPolyData> targetData;

public:
	pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target);
	void calculateSource();
	void calculateTarget();
	vtkSmartPointer<vtkFloatArray> sourcePoints();
	vtkSmartPointer<vtkFloatArray> targetPoints();
	double getAvgSource();
	double getAvgTarget();
	double getMaxS();
	double getMinS();
	double getMaxT();
	double getMinT();
};