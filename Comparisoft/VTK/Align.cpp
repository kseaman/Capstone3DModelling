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
#include <vtkTextProperty.h>

// Constructors
Align::Align() {

};

// Methods

void Align::AlignModels() {
	//Hardcoded files for testing
	//char* filePathSource = NULL;
	//char* filePathTarget = NULL;
	//filePathSource = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerProduction.stl";
	//filePathTarget = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerReference.stl";
	
	vtkSmartPointer<vtkPolyData> source =
		vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPolyData> target =
		vtkSmartPointer<vtkPolyData>::New();

	//Read files
	vtkSmartPointer<vtkSTLReader> sourceReader =
		vtkSmartPointer<vtkSTLReader>::New();
	sourceReader->SetFileName(filePathSource);
	sourceReader->Update();
	source->ShallowCopy(sourceReader->GetOutput());
	
	vtkSmartPointer<vtkSTLReader> targetReader =
		vtkSmartPointer<vtkSTLReader>::New();
	targetReader->SetFileName(filePathTarget);
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

	//We perform the transformation to the target actor so it lines up with the source actor
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter->SetInputData(source);
	transformFilter->SetTransform(landmarkTransform);
	transformFilter->Update();

	// Setup ICP transform
	vtkSmartPointer<vtkIterativeClosestPointTransform> icp =
		vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	icp->SetSource(transformFilter->GetOutput());
	icp->SetTarget(target);
	icp->GetLandmarkTransform()->SetModeToRigidBody();
	icp->DebugOn();
	icp->SetMaximumNumberOfIterations(50);
	//icp->StartByMatchingCentroidsOn();
	icp->Modified();
	icp->Update();

	/* Set-up mappers and actors */
	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkActor> solutionActor =
			vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> targetActor =
			vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkTransformPolyDataFilter> icpTransformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	/* Transform the source points by the ICP solution */
	icpTransformFilter->SetInputConnection(
			transformFilter->GetOutputPort());
	icpTransformFilter->SetTransform(icp);
	icpTransformFilter->Update();

	/* Prepare actors */
	targetMapper->SetInputData(target);
	targetActor->SetMapper(targetMapper);
	targetActor->GetProperty()->SetColor(0.71, 0.95, 0.35);
	targetActor->GetProperty()->SetPointSize(4);

	solutionMapper->SetInputConnection(
			icpTransformFilter->GetOutputPort());
	solutionActor->SetMapper(solutionMapper);
	solutionActor->GetProperty()->SetColor(0.38, 0.62, 0.01);
	solutionActor->GetProperty()->SetPointSize(3);

	/* Assign the actors to variables to return */
	source_actor = solutionActor;
	target_actor = targetActor;

	source_obj = solutionMapper;
	target_obj = targetMapper;

	//icp->StartByMatchingCentroidsOn();

	// Get the resulting transformation matrix (this matrix takes the source points to the target points)
	vtkSmartPointer<vtkMatrix4x4> m = icp->GetMatrix();
	std::cout << "The resulting matrix is: " << *m << std::endl;
}
