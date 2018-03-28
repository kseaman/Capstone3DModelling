#include "PointStorage.h"
#include <vtkCellLocator.h>
using namespace std;


	//constructor
	pointStorage::pointStorage(vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData> target, char* cl, char* eb, char* eu) {
	
		sizeS = source->GetNumberOfPoints();
		sizeT = target->GetNumberOfPoints();
		sourceData = source;
		targetData = target;
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
		if (eunit == "nm") {
			mul = 1000000;
		}
		else if (eunit == "mm") {
			mul = 1;
		}
		else {
			mul = 1;
		}

		thresholdPercentS = 0;
		thresholdPercentT = 0;
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
		int underThreshold = 0;

		for (vtkIdType i = 0; i < sizeS; i++) {

			//get the point to query
			sourceData->GetPoint(i, p);

			//calculate distance
			cellLocator->FindClosestPoint(p, cp, cellId, subId, dist);

			//change distance into the correct unit of mesurement
			dist *= mul;

			//insert the point and its distance into the vector
			scalarsS->SetValue(i, (float)sqrt(dist));

			if (sqrt(dist) > maxDistS) {
				maxDistS = sqrt(dist);
			}
			else if (sqrt(dist) < minDistS) {
				minDistS = sqrt(dist);
			}

			if (sqrt(dist) > ebound) {
				pointsOutsideBoundS++;
			}
			else {
				underThreshold++;
			}

			distTotS += sqrt(dist);
		}
		thresholdPercentS = (underThreshold * 100) / (double)sizeS;
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
		int underThreshold = 0;

		for (vtkIdType i = 0; i < sizeT; i++) {

			//get the point to query
			targetData->GetPoint(i, p);

			//calculate distance
			cellLocator->FindClosestPoint(p, cp, cellId, subId, dist);

			//change distance into the correct unit of mesurement
			dist *= mul;

			//insert the point and its distance into the vector
			scalarsT->SetValue(i, (float)sqrt(dist));

			if (sqrt(dist) > maxDistT) {
				maxDistT = sqrt(dist);
			}
			else if (sqrt(dist) < minDistT) {
				minDistT = sqrt(dist);
			}

			if (sqrt(dist) > ebound) {
				pointsOutsideBoundT++;
			}
			else {
				underThreshold++;
			}

			distTotT += sqrt(dist);
		}
		thresholdPercentT = (underThreshold * 100) / (double)sizeT;
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

	int pointStorage::pointsOverThresholdS() {
		return(pointsOutsideBoundS);
	}

	int pointStorage::pointsOverThresholdT() {
		return(pointsOutsideBoundT);
	}

	double pointStorage::getPercentS() {
		return(thresholdPercentS);
	}

	double pointStorage::getPercentT() {
		return(thresholdPercentT);
	}
