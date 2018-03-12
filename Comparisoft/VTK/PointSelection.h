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

	// Data members
	vtkSmartPointer<vtkPolyData> Data;
	static char screenshot[100];
	ofstream file;
	int count = 0;											/* Determines which pane the point is being selected for */
	int source_count = 0;									/* Number of coordinates selected on the source pane */
	int target_count = 0;									/* Number of coordinates selected on the target pane */
	coordinate source_coordinates[3];						/* Stores selected coordinates on the source pane */
	coordinate target_coordinates[3];						/* Stores selected coordinates on the target pane */
	vtkSmartPointer<vtkDataSetMapper> selectedMapper;		/* Stores hightlighted mapper */
	vtkSmartPointer<vtkActor> selectedActor;				/* Stores hightlighted actor */
	std::vector<vtkSmartPointer<vtkActor> > markedPoints;	/* Stores all the actors that mark points */
	char* filePathSource;									/* Path to the source file*/
	char* filePathTarget;									/* Path to the target file*/
	bool isSourceRenderer = true;							/* Keep track of which renderer is set as default */

	// Methods
	void OnKeyPress() override;
	void OnRightButtonDown() override;
	void OnLeftButtonDown() override;
	void SwitchRenderer();
	vtkSmartPointer<vtkActor> MarkPoint(vtkSmartPointer<vtkCellPicker> p);
};

#endif //VTK_POINTSELECTION_H