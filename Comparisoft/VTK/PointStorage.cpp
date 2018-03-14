#include "PointStorage.h"
#include <vtkCellLocator.h>
using namespace std;


	//constructor
	pointStorage::pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target) {
	
		sizeS = source->GetNumberOfPoints();
		sizeT = target->GetNumberOfPoints();
		sourceList.reserve(sizeS);
		targetList.reserve(sizeT);
		sourceData = source;
		targetData = target;

		//cout << endl << sizeS << endl << sizeT << endl;
	}

	//run distance calculation for source file
	void pointStorage::calculateSource() {

		//set up locator
		vtkSmartPointer<vtkCellLocator> cellLocator =
			vtkSmartPointer<vtkCellLocator>::New();
		cellLocator->SetDataSet(targetData);
		cellLocator->BuildLocator();

		//setup variables for locator
		double cp[3];
		double dist;
		vtkIdType cellId;
		int subId;

		double p[3];

		for (vtkIdType i = 0; i < sizeS; i++) {

			//get the point to query
			sourceData->GetPoint(i, p);

			//calculate distance
			cellLocator->FindClosestPoint(p, cp, cellId, subId, dist);

			//insert the point and its distance into the vector
			point point(i, dist);
			sourceList.push_back(point);
		}

	}

	//run distance calculation for target file
	void pointStorage::calculateTarget() {

		//set up locator
		vtkSmartPointer<vtkCellLocator> cellLocator =
			vtkSmartPointer<vtkCellLocator>::New();
		cellLocator->SetDataSet(sourceData);
		cellLocator->BuildLocator();

		//setup variables for locator
		double cp[3];
		double dist;
		vtkIdType cellId;
		int subId;

		double p[3];

		for (vtkIdType i = 0; i < sizeT; i++) {

			//get the point to query
			sourceData->GetPoint(i, p);

			//calculate distance
			cellLocator->FindClosestPoint(p, cp, cellId, subId, dist);

			//insert the point and its distance into the vector
			point point(i, dist);
			targetList.push_back(point);
		}

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
