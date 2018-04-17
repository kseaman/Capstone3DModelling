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

	/*If fitted model use just 3 point alignment, if matching model use 3 point + ICP*/
	// 0 == matching files, use 3 point + ICP
	vtkSmartPointer<vtkIterativeClosestPointTransform> icp =
		vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	vtkSmartPointer<vtkTransformPolyDataFilter> icpTransformFilter =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	if (strcmp(cam, "0") == 0) {
		std::cout << "We're in!" << std::endl;
		// Setup ICP transform
		icp->SetSource(transformFilter->GetOutput());
		icp->SetTarget(target);
		icp->GetLandmarkTransform()->SetModeToRigidBody();
		icp->DebugOff();
		icp->SetMaximumNumberOfIterations(50);
		//icp->StartByMatchingCentroidsOn();
		icp->Modified();
		icp->Update();

		/* Transform the source points by the ICP solution */
		icpTransformFilter->SetInputConnection(
				transformFilter->GetOutputPort());
		icpTransformFilter->SetTransform(icp);
		icpTransformFilter->Update();
	}

	/* Set-up mappers and actors */
	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkActor> solutionActor =
			vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> targetActor =
			vtkSmartPointer<vtkActor>::New();

	/* Prepare actors */
	targetMapper->SetInputData(target);
	targetActor->SetMapper(targetMapper);
	targetActor->GetProperty()->SetColor(0.71, 0.95, 0.35);
	targetActor->GetProperty()->SetPointSize(4);

	if (strcmp(cam, "0") == 0) {
		solutionMapper->SetInputConnection(
			icpTransformFilter->GetOutputPort());
		source_polyData = icpTransformFilter->GetOutput();
	}
	else {
		solutionMapper->SetInputConnection(
			transformFilter->GetOutputPort());
		source_polyData = transformFilter->GetOutput();
	}
	target_polyData = target;

	solutionActor->SetMapper(solutionMapper);
	solutionActor->GetProperty()->SetColor(0.38, 0.62, 0.01);
	solutionActor->GetProperty()->SetPointSize(3);

	/* Assign the actors to variables to return */
	source_actor = solutionActor;
	target_actor = targetActor;

	source_obj = solutionMapper;
	target_obj = targetMapper;
}
