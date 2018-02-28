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

	int source_count = 0; /* Number of coordinates selected on the source pane */
	int target_count = 0; /* Number of coordinates selected on the target pane */
	int count = 0; /* Determines which pane the point is being selected for */

	coordinate source_coordinates[3]; /* Stores selected coordinates on the source pane */
	coordinate target_coordinates[3]; /* Stores selected coordinates on the target pane */
	char* filePathSource;
	char* filePathTarget;

	/*Stores hightlighted data set*/
	vtkSmartPointer<vtkDataSetMapper> selectedMapper; /*Stores hightlighted mapper*/
	vtkSmartPointer<vtkActor> selectedActor; /*Stores hightlighted actor*/
	
	ofstream file;
	
	vtkRenderer* currRenderer = this->GetDefaultRenderer();
	bool isSourceRenderer = true;

	bool is_open;
    bool thirdPickConfirmed = false;
    bool sixthPickConfirmed = false;

	// Methods
	void OnKeyPress() override;
	void OnRightButtonDown() override ;
	void SwitchRenderer();


	static char screenshot[100];
};

#endif //VTK_POINTSELECTION_H