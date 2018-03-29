/******************************************************************************
@file		Align.h
@author 	Emerson Kirby

@details	This file handles the alignment of the models
******************************************************************************/
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkActor.h>
#include <vtkTextActor.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRendererCollection.h>
#include <vtkPolyDataMapper.h>


class Align {

public:
	//Data members
	vtkSmartPointer<vtkPoints> sourcePoints;
	vtkSmartPointer<vtkPoints> targetPoints;
	vtkSmartPointer<vtkActor> source_actor;
	vtkSmartPointer<vtkActor> target_actor;
	vtkSmartPointer<vtkPolyData> source_polyData;
	vtkSmartPointer<vtkPolyData> target_polyData;
	vtkSmartPointer<vtkPolyDataMapper> target_obj;
	vtkSmartPointer<vtkPolyDataMapper> source_obj;
	vtkSmartPointer<vtkTextActor> status_bar;
	vtkRenderWindowInteractor *Interactor;
	char* filePathSource;
	char* filePathTarget;
	char* cam;

	//Constructors
	Align();
	
	//Methods
	void AlignModels();
};
