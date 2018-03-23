#include "PointStorage.h"
#include <vtkCellLocator.h>
using namespace std;


	//constructor
	pointStorage::pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target, char* cl, char* eb, char* eu) {
	
		sizeS = source->GetNumberOfPoints();
		sizeT = target->GetNumberOfPoints();
		//sourceList.reserve(sizeS);
		//targetList.reserve(sizeT);
		sourceData = source;
		targetData = target;
		maxDistS = 0;
		minDistS = 0;
		maxDistT = 0;
		minDistT = 0;
		scalarsS = vtkSmartPointer<vtkFloatArray>::New();
		scalarsT = vtkSmartPointer<vtkFloatArray>::New();
		scalarsS->SetNumberOfValues(sizeS);
		scalarsT->SetNumberOfValues(sizeT);

		clevel = atoi(cl);
		printf("clevel atoi = %d\n", clevel);
		ebound = atoi(eb);
		printf("ebound atoi = %d\n", ebound);
		eunit = eu;
		cout << eunit;

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
			//point point(i, (float)sqrt(dist));
			//sourceList.push_back(point);
			scalarsS->SetValue(i, (float)sqrt(dist));

			if (sqrt(dist) > maxDistS) {
				maxDistS = sqrt(dist);
			}
			else if (sqrt(dist) < minDistS) {
				minDistS = sqrt(dist);
			}

			distTotS += sqrt(dist);
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
			targetData->GetPoint(i, p);

			//calculate distance
			cellLocator->FindClosestPoint(p, cp, cellId, subId, dist);

			//insert the point and its distance into the vector
			//point point(i, (float)sqrt(dist));
			//targetList.push_back(point);
			scalarsT->SetValue(i, (float)sqrt(dist));

			if (sqrt(dist) > maxDistT) {
				maxDistT = sqrt(dist);
			}
			else if (sqrt(dist) < minDistT) {
				minDistT = sqrt(dist);
			}

			distTotT += sqrt(dist);
		}

	}

	vtkSmartPointer<vtkFloatArray> pointStorage::sourcePoints() {
		return scalarsS;
	}

	vtkSmartPointer<vtkFloatArray> pointStorage::targetPoints() {
		return scalarsT;
	}

	double pointStorage::getAvgSource() {
		return (distTotS / sizeS);
	}

	double pointStorage::getAvgTarget() {
		return (distTotT / sizeT);
	}

	double pointStorage::getMaxS() {
		return(maxDistS);
	}

	double pointStorage::getMinS() {
		return(minDistS);
	}

	double pointStorage::getMaxT() {
		return(maxDistT);
	}

	double pointStorage::getMinT() {
		return(minDistT);
	}
