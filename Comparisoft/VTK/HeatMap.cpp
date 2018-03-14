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

	/* Set up cell locator for calculating distances with respect to the source object */
	vtkSmartPointer<vtkCellLocator> cellLocator =
			vtkSmartPointer<vtkCellLocator>::New();
	cellLocator->SetDataSet(sourceObj->GetInput());
	cellLocator->BuildLocator();

	/* Calculate distances to closest point on target object */
	double closestPoint[3];	/* The coordinates of the closest point */
	double distanceSquared; /* The squared distance to the closest point */
	vtkIdType cellId; 		/* The cell id of the cell containing the closest point */
	int subId;

	int numPts = (int) sourceObj->GetInput()->GetPoints()->GetNumberOfPoints();
	std::cout << "Num points on source object: " << numPts << "\n";

	vtkSmartPointer<vtkFloatArray> scalars =
			vtkSmartPointer<vtkFloatArray>::New();
	scalars->SetNumberOfValues(numPts);

	double min = 0;
	double max = 0;

	for( int i = 0; i < numPts; ++i )
	{
		cellLocator->FindClosestPoint(targetObj->GetInput()->GetPoint(i), closestPoint, cellId, subId, distanceSquared);
		scalars->SetValue(i, (float) sqrt(distanceSquared));
		std::cout << "Iteration: " << i << ", cellId: " << cellId << ", sqrt(distance): "<< sqrt(distanceSquared) <<"\n";

		if (sqrt(distanceSquared) > max) {
			max = sqrt(distanceSquared);
		}
		else if (sqrt(distanceSquared) < min) {
			min = sqrt(distanceSquared);
		}
	}

	/* Assign scalar values to source object */
	vtkSmartPointer<vtkPolyData> sourceData =
			vtkSmartPointer<vtkPolyData>::New();
	sourceData->DeepCopy(sourceObj->GetInput());
	sourceData->GetPointData()->SetScalars(scalars);

	vtkSmartPointer<vtkPolyData> targetData =
			vtkSmartPointer<vtkPolyData>::New();
	targetData->DeepCopy(targetObj->GetInput());

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

	sourceObjActor->SetMapper(sourceMapper);
	targetObjActor->SetMapper(targetMapper);

	scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(sourceMapper->GetLookupTable());
	scalarBar->SetTitle("Distance to closest point");
	scalarBar->SetNumberOfLabels(4);

	/* Create a lookup table to share between the source mapper and the scalar bar */
	vtkSmartPointer<vtkLookupTable> hueLut = vtkSmartPointer<vtkLookupTable>::New();
	hueLut->SetTableRange (min, max);
	hueLut->SetHueRange (0, 0.9);
	hueLut->SetSaturationRange (1, 1);
	hueLut->SetValueRange (1, 1);
	hueLut->Build();

	sourceMapper->SetLookupTable(hueLut);
	scalarBar->SetLookupTable(hueLut);
}
