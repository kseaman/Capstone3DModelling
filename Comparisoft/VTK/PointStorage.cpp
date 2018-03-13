#include "PointStorage.h"
using namespace std;


	//constructor
	pointStorage::pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target) {
	
		sizeS = source->GetNumberOfPoints();
		sizeT = target->GetNumberOfPoints();
		sourceList.reserve(sizeS);
		targetList.reserve(sizeT);
		sourceData = source;
		targetData = target;
	}

	void pointStorage::calculateSource() {

	}

	void pointStorage::calculateTarget() {

	}

	vector<point> pointStorage::sourcePoints() {
		return sourceList;
	}

	vector<point> pointStorage::targetPoints() {
		return targetList;
	}

	double pointStorage::getAvgSource() {
		return (distS / sizeS);
	}

	double pointStorage::getAvgTarget() {
		return (distT / sizeT);
	}
