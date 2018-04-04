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

double avgSource = 0;
double avgTarget = 0;
double perSource = 0;
double perTarget = 0;

HeatMap::HeatMap() = default;

void HeatMap::DisplayHeatMap() {

	pointStorage points = pointStorage(sourceObj->GetInput(), targetObj->GetInput(), clevel, ebound, eunit);
	points.calculateSource();
	points.calculateTarget();

	std::string threshold_float(ebound);
	float error = std::stof(threshold_float);

	/* Assign scalar values to source object */
	vtkSmartPointer<vtkPolyData> sourceData =
			vtkSmartPointer<vtkPolyData>::New();
	sourceData->DeepCopy(sourceObj->GetInput());
	sourceData->GetPointData()->SetScalars(points.sourcePoints());
	sourcePoints = points.sourcePoints();

	vtkSmartPointer<vtkPolyData> targetData =
			vtkSmartPointer<vtkPolyData>::New();
	targetData->DeepCopy(targetObj->GetInput());
	targetData->GetPointData()->SetScalars(points.targetPoints());
	targetPoints = points.targetPoints();

	avgSource = points.getAvgSource();
	avgTarget = points.getAvgTarget();
	perSource = points.getPercentS();
	perTarget = points.getPercentT();

	maxS = points.getMaxS();
	maxT = points.getMaxT();

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

	targetMapper->ScalarVisibilityOn();
	targetMapper->SetScalarModeToUsePointData();
	targetMapper->SetColorModeToMapScalars();

	sourceObjActor->SetMapper(sourceMapper);
	targetObjActor->SetMapper(targetMapper);

	scalarBarS = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBarS->SetLookupTable(sourceMapper->GetLookupTable());
	if (strcmp(eunit, "nm") == 0) {
		/* Distance unit is nm */
		scalarBarS->SetTitle("Distance (nm)");
		//sourceMapper->SetScalarRange(-(error*1000000), (error*1000000)); /* Convert mm to nm */
		sourceMapper->SetScalarRange(-error, error);
	}
	else {
		/* Distance unit is mm (default) */
		scalarBarS->SetTitle("Distance (mm)");
		sourceMapper->SetScalarRange(-error, error); /* Default */
	}
	scalarBarS->SetNumberOfLabels(5);

	scalarBarT = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBarT->SetLookupTable(targetMapper->GetLookupTable());
	if (strcmp(eunit, "nm") == 0) {
		/* Distance unit is nm */
		scalarBarT->SetTitle("Distance (nm)");
		//targetMapper->SetScalarRange(-(error*1000000), (error*1000000)); /* Convert mm to nm */
		targetMapper->SetScalarRange(-error, error);
	}
	else {
		/* Distance unit is mm (default) */
		scalarBarT->SetTitle("Distance (mm)");
		targetMapper->SetScalarRange(-error, error); /* Default */
	}
	scalarBarT->SetNumberOfLabels(5);

	/* Create a lookup table to share between the source mapper and the scalar bar */
	vtkSmartPointer<vtkLookupTable> hueLutS = vtkSmartPointer<vtkLookupTable>::New();

	if (strcmp(eunit, "nm") == 0) {
		/* Distance unit is nm */
		//hueLutS->SetTableRange(-(error*1000000), (error*1000000)); /* Convert mm to nm */
		targetMapper->SetScalarRange(-error, error);
	}
	else {
		/* Distance unit is mm (default) */
		hueLutS->SetTableRange(-error, error);
	}
	hueLutS->SetHueRange (0.65, 0);
	hueLutS->SetSaturationRange (1, 1);
	hueLutS->SetValueRange (1, 1);
	hueLutS->Build();

	sourceMapper->SetLookupTable(hueLutS);
	scalarBarS->SetLookupTable(hueLutS);

	vtkSmartPointer<vtkLookupTable> hueLutT = vtkSmartPointer<vtkLookupTable>::New();

	if (strcmp(eunit, "nm") == 0) {
		/* Distance unit is nm */
		hueLutT->SetTableRange(-(error*1000000), (error*1000000)); /* Convert mm to nm */
	}
	else {
		/* Distance unit is mm (default) */
		hueLutT->SetTableRange(-error, error);
	}
	hueLutT->SetHueRange(0.65, 0);
	hueLutT->SetSaturationRange(1, 1);
	hueLutT->SetValueRange(1, 1);
	hueLutT->Build();

	targetMapper->SetLookupTable(hueLutT);
	scalarBarT->SetLookupTable(hueLutT);
}
