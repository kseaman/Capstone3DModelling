/******************************************************************************/
/**
@file		HeatMap.cpp
@reference	HeatMap.h
@author 	Dana Klamut, Karn Seaman
@details	This file handles the heat map displaying the distances between
 			the 3D objects.
*/
/******************************************************************************/

#include "HeatMap.h"

HeatMap::HeatMap() = default;

void HeatMap::DisplayHeatMap() {

	pointStorage points = pointStorage(sourceObj->GetInput(), targetObj->GetInput());
	points.calculateSource();
	points.calculateTarget();

	///* Set up cell locator for calculating distances with respect to the source object */
	//vtkSmartPointer<vtkCellLocator> cellLocator =
	//		vtkSmartPointer<vtkCellLocator>::New();
	//cellLocator->SetDataSet(sourceObj->GetInput());
	//cellLocator->BuildLocator();

	///* Calculate distances to closest point on target object */
	//double closestPoint[3];	/* The coordinates of the closest point */
	//double distanceSquared; /* The squared distance to the closest point */
	//vtkIdType cellId; 		/* The cell id of the cell containing the closest point */
	//int subId;

	//int numPts = (int) sourceObj->GetInput()->GetPoints()->GetNumberOfPoints();
	//std::cout << "Num points on source object: " << numPts << "\n";

	//vtkSmartPointer<vtkFloatArray> scalars =
	//		vtkSmartPointer<vtkFloatArray>::New();
	//scalars->SetNumberOfValues(numPts);

	//double min = 0;
	//double max = 0;

	//for( int i = 0; i < numPts; ++i )
	//{
	//	cellLocator->FindClosestPoint(targetObj->GetInput()->GetPoint(i), closestPoint, cellId, subId, distanceSquared);
	//	scalars->SetValue(i, (float) sqrt(distanceSquared));
	//	std::cout << "Iteration: " << i << ", cellId: " << cellId << ", sqrt(distance): "<< sqrt(distanceSquared) <<"\n";

	//	if (sqrt(distanceSquared) > max) {
	//		max = sqrt(distanceSquared);
	//	}
	//	else if (sqrt(distanceSquared) < min) {
	//		min = sqrt(distanceSquared);
	//	}
	//}

	double minS = points.getMinS();
	double maxS = points.getMaxS();
	double minT = points.getMinT();
	double maxT = points.getMaxT();

	/* Assign scalar values to source object */
	vtkSmartPointer<vtkPolyData> sourceData =
			vtkSmartPointer<vtkPolyData>::New();
	sourceData->DeepCopy(sourceObj->GetInput());
	//sourceData->GetPointData()->SetScalars(scalars);
	sourceData->GetPointData()->SetScalars(points.sourcePoints());

	vtkSmartPointer<vtkPolyData> targetData =
			vtkSmartPointer<vtkPolyData>::New();
	targetData->DeepCopy(targetObj->GetInput());
	targetData->GetPointData()->SetScalars(points.targetPoints());

	/* Set up mappers */
	vtkSmartPointer<vtkPolyDataMapper> sourceMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();

	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();

#if VTK_MAJOR_VERSION <= 5
	sourceMapper->SetInput(sourceData);
	targetMapper->SetInput(targetData);
#else
	sourceMapper->SetInputData(sourceData);
	targetMapper->SetInputData(targetData);
#endif

	sourceMapper->ScalarVisibilityOn();
	sourceMapper->SetScalarModeToUsePointData();
	sourceMapper->SetColorModeToMapScalars();
	sourceMapper->SetScalarRange(minS, maxS);

	targetMapper->ScalarVisibilityOn();
	targetMapper->SetScalarModeToUsePointData();
	targetMapper->SetColorModeToMapScalars();
	targetMapper->SetScalarRange(minT, maxT);

	sourceObjActor->SetMapper(sourceMapper);
	targetObjActor->SetMapper(targetMapper);

	scalarBarS = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBarS->SetLookupTable(sourceMapper->GetLookupTable());
	scalarBarS->SetTitle("Distance to closest point");
	scalarBarS->SetNumberOfLabels(4);

	scalarBarT = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBarT->SetLookupTable(targetMapper->GetLookupTable());
	scalarBarT->SetTitle("Distance to closest point");
	scalarBarT->SetNumberOfLabels(4);

	/* Create a lookup table to share between the source mapper and the scalar bar */
	vtkSmartPointer<vtkLookupTable> hueLutS = vtkSmartPointer<vtkLookupTable>::New();
	hueLutS->SetTableRange (minS, maxS);
	hueLutS->SetHueRange (0, 0.9);
	hueLutS->SetSaturationRange (1, 1);
	hueLutS->SetValueRange (1, 1);
	hueLutS->Build();

	sourceMapper->SetLookupTable(hueLutS);
	scalarBarS->SetLookupTable(hueLutS);

	vtkSmartPointer<vtkLookupTable> hueLutT = vtkSmartPointer<vtkLookupTable>::New();
	hueLutT->SetTableRange(minT, maxT);
	hueLutT->SetHueRange(0, 0.9);
	hueLutT->SetSaturationRange(1, 1);
	hueLutT->SetValueRange(1, 1);
	hueLutT->Build();

	targetMapper->SetLookupTable(hueLutT);
	scalarBarT->SetLookupTable(hueLutT);
}
