/******************************************************************************/
/**
@file		PointSelection.h
@author 	Dana Klamut
@details	This file handles the point selection on the data sets.
Adapted from: https://www.vtk.org/Wiki/VTK/Examples/Cxx/Interaction/PointPicker
*/
/******************************************************************************/

#ifndef VTK_POINTSELECTION_H
#define VTK_POINTSELECTION_H


#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkAutoInit.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPlaneSource.h>
#include <vtkCellPicker.h>
#include <vtkProperty.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkVertexGlyphFilter.h>

/**
@brief Stores selected coordinates on data sets.
*/
struct coordinate {
	double x_val;
	double y_val;
	double z_val;
};

class PointSelection : public vtkInteractorStyleTrackballCamera {

public:


	static PointSelection* New();
	vtkTypeMacro(PointSelection, vtkInteractorStyleTrackballCamera);

	vtkSmartPointer<vtkPolyData> Data;

	int ref_count = 0; /* Number of coordinates selected on the reference pane */
	int prod_count = 0; /* Number of coordinates selected on the production pane */
	int count = 0; /* Determines which pane the point is being selected for */

	coordinate ref_coordinates[3]; /* Stores selected coordinates on the reference pane */
	coordinate prod_coordinates[3]; /* Stores selected coordinates on the production pane */
	char* filePathRef;
	char* filePathProd;


	/*Stores hightlighted data set*/
	vtkSmartPointer<vtkDataSetMapper> selectedMapper; /*Stores hightlighted mapper*/
	vtkSmartPointer<vtkActor> selectedActor; /*Stores hightlighted actor*/


	ofstream file;

	bool is_open;
	bool is_completed;
    bool thirdPickConfirmed = false;
    bool sixthPickConfirmed = false;
    bool controlPressed;
	void OnRightButtonDown() override ;

};

#endif //VTK_POINTSELECTION_H