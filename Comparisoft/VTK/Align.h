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
	vtkSmartPointer<vtkActor> refActor;
	vtkSmartPointer<vtkActor> prodActor;
	char* filePathRef;
	char* filePathProd;

	//Constructors
	Align();
	
	//Methods
	void AlignModels();
};
