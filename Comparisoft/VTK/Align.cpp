#include "Align.h"
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkProperty.h>
#include <vtkLandmarkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkIterativeClosestPointTransform.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockDataGroupFilter.h>
#include <vtkProcrustesAlignmentFilter.h>

// Constructors
Align::Align() {

};


// Methods

void Align::AlignModels() {
	//Hardcoded files for testing
	//char* filePathReference = NULL;
	//char* filePathProduction = NULL;
	//filePathReference = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerProduction.stl";
	//filePathProduction = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerReference.stl";
	
	vtkSmartPointer<vtkPolyData> source =
		vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPolyData> target =
		vtkSmartPointer<vtkPolyData>::New();

	//Read files
	vtkSmartPointer<vtkSTLReader> sourceReader =
		vtkSmartPointer<vtkSTLReader>::New();
	sourceReader->SetFileName(filePathRef);
	sourceReader->Update();
	source->ShallowCopy(sourceReader->GetOutput());
	
	vtkSmartPointer<vtkSTLReader> targetReader =
		vtkSmartPointer<vtkSTLReader>::New();
	targetReader->SetFileName(filePathProd);
	targetReader->Update();
	target->ShallowCopy(targetReader->GetOutput());

	//Perform the landmark transform to do a rough alignment
	vtkSmartPointer<vtkLandmarkTransform> landmarkTransform =
		vtkSmartPointer<vtkLandmarkTransform>::New();
	landmarkTransform->SetSourceLandmarks(sourcePoints);
	landmarkTransform->SetTargetLandmarks(targetPoints);
	//We only want rotation and translation so set to RigidBody
	landmarkTransform->SetModeToRigidBody();
	landmarkTransform->Modified();
	landmarkTransform->Update();

	//We perform the transformation to the production actor so it lines up with the reference actor
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter->SetInputData(source);
	transformFilter->SetTransform(landmarkTransform);
	transformFilter->Update();

	// Setup ICP transform
	vtkSmartPointer<vtkIterativeClosestPointTransform> icp =
		vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	icp->SetSource(source);
	icp->SetTarget(target);
	icp->GetLandmarkTransform()->SetModeToRigidBody();
	icp->DebugOn();
	icp->SetMaximumNumberOfIterations(100);
	//icp->StartByMatchingCentroidsOn();
	icp->Modified();
	icp->Update();

	// Get the resulting transformation matrix (this matrix takes the source points to the target points)
	vtkSmartPointer<vtkMatrix4x4> m = icp->GetMatrix();
	std::cout << "The resulting matrix is: " << *m << std::endl;
	
	// Transform the source points by the ICP solution
	vtkSmartPointer<vtkTransformPolyDataFilter> icpTransformFilter =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	icpTransformFilter->SetInputConnection(transformFilter->GetOutputPort());
	icpTransformFilter->SetTransform(icp);
	icpTransformFilter->Update();
	
	//Prepare the actors
	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	targetMapper->SetInputData(target);
	vtkSmartPointer<vtkActor> targetActor =
		vtkSmartPointer<vtkActor>::New();
	targetActor->SetMapper(targetMapper);
	targetActor->GetProperty()->SetColor(0, 1, 0);
	targetActor->GetProperty()->SetPointSize(4);
	vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	solutionMapper->SetInputConnection(icpTransformFilter->GetOutputPort());
	vtkSmartPointer<vtkActor> solutionActor =
		vtkSmartPointer<vtkActor>::New();
	solutionActor->SetMapper(solutionMapper);
	solutionActor->GetProperty()->SetColor(0, 0, 1);
	solutionActor->GetProperty()->SetPointSize(3);

	//Assign the actors to variables to return
	refActor = solutionActor;
	prodActor = targetActor;
}