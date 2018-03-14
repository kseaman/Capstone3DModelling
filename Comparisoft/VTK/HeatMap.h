/******************************************************************************/
/**
@file		HeatMap.h
@author 	Dana Klamut, Karn Seaman
@details	This file handles the heat map displaying the distances between
 			the 3D objects.
*/
/******************************************************************************/

#ifndef HEATMAP_H
#define HEATMAP_H

#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellLocator.h>
#include <vtkScalarBarActor.h>
#include <vtkPointData.h>
#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkActor.h>

class HeatMap {

public:
	vtkSmartPointer<vtkPolyDataMapper> targetObj;
	vtkSmartPointer<vtkPolyDataMapper> sourceObj;

	vtkSmartPointer<vtkActor> sourceObjActor;
	vtkSmartPointer<vtkActor> targetObjActor;

	vtkSmartPointer<vtkScalarBarActor> scalarBar;

	HeatMap();

	void DisplayHeatMap();
};


#endif //HEATMAP_H
