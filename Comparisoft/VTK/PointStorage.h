#pragma once
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkFloatArray.h>
using namespace std;

class pointStorage {

private: 

	int clevel;
	int ebound;
	string eunit;
	int mul;
	int pointsOutsideBoundS = 0;
	int pointsOutsideBoundT = 0;
	double thresholdPercentS;
	double thresholdPercentT;
	int sizeS;
	int sizeT;
	double distTotS;
	double distTotT;
	double maxDistS = 0;
	double minDistS = 0;
	double maxDistT = 0;
	double minDistT = 0;
	vtkSmartPointer<vtkFloatArray> scalarsS;
	vtkSmartPointer<vtkFloatArray> scalarsT;
	vtkSmartPointer<vtkPolyData> sourceData;
	vtkSmartPointer<vtkPolyData> targetData;

public:
	pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target, char* cl, char* eb, char* eu);
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
	int pointsOverThresholdS();
	int pointsOverThresholdT();
	double getPercentS();
	double getPercentT();
};