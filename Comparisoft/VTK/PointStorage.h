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
	double thresholdPercentS;
	double thresholdPercentT;
	int sizeS;
	int sizeT;
	double distTotS;
	double distTotT;
	double maxDistS;
	double minDistS;
	double maxDistT;
	double minDistT;
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
	double getPercentS();
	double getPercentT();
};