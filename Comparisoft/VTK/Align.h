/******************************************************************************
@file		Align.h
@author 	Emerson Kirby

@details	This file handles the alignment of the models
******************************************************************************/
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkActor.h>

class Align {

public:
	//Data members
	vtkSmartPointer<vtkPoints> sourcePoints;
	vtkSmartPointer<vtkPoints> targetPoints;
	vtkSmartPointer<vtkActor> source_actor;
	vtkSmartPointer<vtkActor> target_actor;
	char* filePathSource;
	char* filePathTarget;

	//Constructors
	Align();
	
	//Methods
	void AlignModels();
};
