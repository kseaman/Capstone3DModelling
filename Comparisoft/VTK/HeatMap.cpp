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

	pointStorage points = pointStorage(sourceObj->GetInput(), targetObj->GetInput(), clevel, ebound, eunit);
	points.calculateSource();
	points.calculateTarget();

	double minS = points.getMinS();
	double maxS = points.getMaxS();
	double minT = points.getMinT();
	double maxT = points.getMaxT();

	/* Assign scalar values to source object */
	vtkSmartPointer<vtkPolyData> sourceData =
			vtkSmartPointer<vtkPolyData>::New();
	sourceData->DeepCopy(sourceObj->GetInput());
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
	hueLutS->SetHueRange (0.7, 0);
	hueLutS->SetSaturationRange (1, 1);
	hueLutS->SetValueRange (1, 1);
	hueLutS->Build();

	sourceMapper->SetLookupTable(hueLutS);
	scalarBarS->SetLookupTable(hueLutS);

	vtkSmartPointer<vtkLookupTable> hueLutT = vtkSmartPointer<vtkLookupTable>::New();
	hueLutT->SetTableRange(minT, maxT);
	hueLutT->SetHueRange(0, 0.85);
	hueLutT->SetSaturationRange(1, 1);
	hueLutT->SetValueRange(1, 1);
	hueLutT->Build();

	targetMapper->SetLookupTable(hueLutT);
	scalarBarT->SetLookupTable(hueLutT);
}
