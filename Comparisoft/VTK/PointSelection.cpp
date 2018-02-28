//
// Created by Zifang Jiang on 2018-01-29.
//
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include "vtkCellPicker.h"
#include "vtkSelectionNode.h"

#include "vtkSelection.h"
#include "vtkExtractSelection.h"
#include "vtkDataSetMapper.h"
#include "vtkUnstructuredGrid.h"
#include <vtkCamera.h>


/******************************************************************************/
/**
@file		PointSelection.cpp
@reference	PointSelection.h
@author 	Dana Klamut
@details	This file handles the point selection on the data sets.
Adapted from: https://www.vtk.org/Wiki/VTK/Examples/Cxx/Interaction/PointPicker
*/
/******************************************************************************/


#include "PointSelection.h"
#include "Align.h"
#include "vtkActor.h"

char PointSelection::screenshot[100] = "";

// Switch between renderers. Used for highlighting points
void PointSelection::SwitchRenderer() 
{
	vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
	if (isSourceRenderer) {
		//Change currRenderer to target renderer
		this->SetDefaultRenderer((vtkRenderer*)panes->GetItemAsObject(1));
		isSourceRenderer = false;
	}
	else {
		//Change currRenderer to source renderer
		this->SetDefaultRenderer((vtkRenderer*)panes->GetItemAsObject(0));
		isSourceRenderer = true;
	}

	// Change data into new renderer's dataset
	vtkActorCollection* actors = this->GetDefaultRenderer()->GetActors();
	vtkActor* Actor = (vtkActor*)actors->GetItemAsObject(0);
	vtkDataSetMapper* mapper = (vtkDataSetMapper*)Actor->GetMapper();
	vtkPolyData* triangleFilter2;
	triangleFilter2 = dynamic_cast<vtkPolyData *>(mapper->GetInputAsDataSet());
	Data = triangleFilter2;
}

/**
@brief Alter the inherited OnRightButtonDown() of
vtkInteractorStyleTrackballCamera to be compatible with our intended use.
-Picks alternate from source to target
-Ctrl+Z to toggle locking of target pane
@returns void
*/
void PointSelection::OnRightButtonDown()
{
	// Get the location of the click (in window coordinates)
	int* pos = this->GetInteractor()->GetEventPosition();
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.0005);

	// Pick from this location.
	picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());
	double* picked = picker->GetPickPosition();

	//making sure the pick is not off image (no cellData is cellId =1 )
	if (picker->GetCellId() != -1)
	{
		//storing cellId into ids
		vtkSmartPointer<vtkIdTypeArray> ids =
			vtkSmartPointer<vtkIdTypeArray>::New();
		ids->SetNumberOfComponents(1);
		ids->InsertNextValue(picker->GetCellId());

		//storing id into node
		vtkSmartPointer<vtkSelectionNode> selectionNode =
			vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(ids);

		//node stored into selection
		vtkSmartPointer<vtkSelection> selection =
			vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		//set both mapper dataset Data and selection consisting selected node as input for extractSelection
		vtkSmartPointer<vtkExtractSelection> extractSelection =
			vtkSmartPointer<vtkExtractSelection>::New();
		extractSelection->SetInputData(0, this->Data);
		extractSelection->SetInputData(1, selection);
		extractSelection->Update();

		vtkSmartPointer<vtkUnstructuredGrid> selected =
			vtkSmartPointer<vtkUnstructuredGrid>::New();
		selected->ShallowCopy(extractSelection->GetOutput());

		//setting mapper and actor here ensures selection remain highlighted
		selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		selectedActor = vtkSmartPointer<vtkActor>::New();

		selectedMapper->SetInputData(selected);
		selectedActor->SetMapper(selectedMapper);
		selectedActor->GetProperty()->EdgeVisibilityOn();
		selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
		selectedActor->GetProperty()->SetLineWidth(100);

		count++;

		switch (count) {
			case 1: {
				selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				SwitchRenderer();
				source_coordinates[source_count] = { picked[0], picked[1], picked[2] }; //stores source coordinates
				source_count++;
				break;
			}
			case 2: {
				selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				SwitchRenderer();
				target_coordinates[target_count] = { picked[0], picked[1], picked[2] };
				target_count++;
				break;
			}
			case 3: {
				selectedActor->GetProperty()->SetEdgeColor(0, 1, 0);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				SwitchRenderer();
				source_coordinates[source_count] = { picked[0], picked[1], picked[2] };
				source_count++;
				break;
			}
			case 4: {
				selectedActor->GetProperty()->SetEdgeColor(0, 1, 0);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				SwitchRenderer();
				target_coordinates[target_count] = { picked[0], picked[1], picked[2] };
				target_count++;
				break;
			}
			case 5: {
				selectedActor->GetProperty()->SetEdgeColor(0, 0, 1);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				SwitchRenderer();
				source_coordinates[source_count] = { picked[0], picked[1], picked[2] };
				source_count++;
				break;
			}
			case 6: {
				selectedActor->GetProperty()->SetEdgeColor(0, 0, 1);
				this->GetDefaultRenderer()->AddActor(selectedActor);
				target_coordinates[target_count] = { picked[0], picked[1], picked[2] };
				target_count++;

				Align bottomPanel;
				bottomPanel.filePathTarget = this->filePathTarget;
				bottomPanel.filePathSource = this->filePathSource;

				//Get renderer for bottom viewpoint (it is the third renderer in the collection)
				vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
				vtkRenderer* combinedPane = (vtkRenderer*)panes->GetItemAsObject(2);

				//Insert points into bottom panel
				bottomPanel.sourcePoints = vtkSmartPointer<vtkPoints>::New();
				double sourcePoint0[3] = { source_coordinates[0].x_val, source_coordinates[0].y_val, source_coordinates[0].z_val };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint0);
				double sourcePoint1[3] = { source_coordinates[1].x_val, source_coordinates[1].y_val, source_coordinates[1].z_val };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint1);
				double sourcePoint2[3] = { source_coordinates[2].x_val, source_coordinates[2].y_val, source_coordinates[2].z_val };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint2);

				bottomPanel.targetPoints = vtkSmartPointer<vtkPoints>::New();
				double targetPoint0[3] = { target_coordinates[0].x_val, target_coordinates[0].y_val, target_coordinates[0].z_val };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint0);
				double targetPoint1[3] = { target_coordinates[1].x_val, target_coordinates[1].y_val, target_coordinates[1].z_val };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint1);
				double targetPoint2[3] = { target_coordinates[2].x_val, target_coordinates[2].y_val, target_coordinates[2].z_val };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint2);

				// Test source points
				/*double sourcePoint1[3] = { 0.0, 0.0, 1.0 };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint1);
				double sourcePoint2[3] = { 0.0, 0.0, 0.0 };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint2);
				double sourcePoint3[3] = { 0.0, 0.0, 1.0 };
				bottomPanel.sourcePoints->InsertNextPoint(sourcePoint3);*/

				// Test target points
				/*double targetPoint1[3] = { 0.0, 0.0, 1.1 };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint1);
				double targetPoint2[3] = { 0.0, 0.0, 0.0 };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint2);
				double targetPoint3[3] = { 0.0, 0.0, 1.0 };
				bottomPanel.targetPoints->InsertNextPoint(targetPoint3);*/

				//Add the transformed actors to , which is returned by bottompanel.alignmodels
				bottomPanel.source_actor = vtkSmartPointer<vtkActor>::New();
				bottomPanel.target_actor = vtkSmartPointer<vtkActor>::New();
				
				bottomPanel.AlignModels();

				combinedPane->AddActor(bottomPanel.target_actor);
				combinedPane->AddActor(bottomPanel.source_actor);
				combinedPane->ResetCamera();
				this->Interactor->GetRenderWindow()->Render();

				// We now have sufficient click data, pass to our alignment
				std::cout << "Point 1 on R Pane (x, y, z): " << source_coordinates[0].x_val << " "
					<< source_coordinates[0].y_val << " " << source_coordinates[0].z_val << std::endl;
				std::cout << "Point 2 on R Pane (x, y, z): " << source_coordinates[1].x_val << " "
					<< source_coordinates[1].y_val << " " << source_coordinates[1].z_val << std::endl;
				std::cout << "Point 3 on R Pane (x, y, z): " << source_coordinates[2].x_val << " "
					<< source_coordinates[2].y_val << " " << source_coordinates[2].z_val << std::endl;
				std::cout << std::endl;

				std::cout << "Point 1 on P Pane (x, y, z): " << target_coordinates[0].x_val << " "
					<< target_coordinates[0].y_val << " " << target_coordinates[0].z_val << std::endl;
				std::cout << "Point 2 on P Pane (x, y, z): " << target_coordinates[1].x_val << " "
					<< target_coordinates[1].y_val << " " << target_coordinates[1].z_val << std::endl;
				std::cout << "Point 3 on P Pane (x, y, z): " << target_coordinates[2].x_val << " "
					<< target_coordinates[2].y_val << " " << target_coordinates[2].z_val << std::endl;

				//change default renderer to renderer 3, such that renderer 3 can be accessed
				this->SetDefaultRenderer(combinedPane);

				/* Screen shot the entire window once the files have been aligned */
				/* This code has been adapted from: VTK/Examples/Cxx/Utilities/Screenshot */
				/* ref: https://www.vtk.org/Wiki/VTK/Examples/Cxx/Utilities/Screenshot */
				vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
					vtkSmartPointer<vtkWindowToImageFilter>::New();
				windowToImageFilter->SetInput(this->Interactor->GetRenderWindow());
				windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
				windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
				windowToImageFilter->Update();
				vtkSmartPointer<vtkPNGWriter> writer =
					vtkSmartPointer<vtkPNGWriter>::New();
				writer->SetFileName(PointSelection::screenshot);
				writer->SetInputConnection(windowToImageFilter->GetOutputPort());
				writer->Write();

				break;
			}
		}
	}
	//forward events
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

// Implementing hot keys
void PointSelection::OnKeyPress() {
	// Get the keypress
	vtkRenderWindowInteractor *rwi = this->Interactor;
	std::string key = rwi->GetKeySym();

	std::cout << "Pressed " << key << std::endl;

	// TOGGLE LOCKED PANE
	if (this->Interactor->GetControlKey() && key == "l") {
		vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
		vtkRenderer* renderer1 = (vtkRenderer*)panes->GetItemAsObject(0);
		vtkRenderer* renderer2 = (vtkRenderer*)panes->GetItemAsObject(1);
		
		if ((renderer2->GetActiveCamera()) == (renderer1->GetActiveCamera())) {
			// Lock the pane
			renderer2->SetActiveCamera(vtkCamera::New());
			renderer2->ResetCamera();
		}
		else {
			// Unlock the pane
			renderer2->SetActiveCamera(renderer1->GetActiveCamera());
			renderer2->ResetCamera();
		}
	}

	//if (this->Interactor->GetControlKey()) {
	//	std::string key = this->Interactor->GetKeySym();  //need to be filled to start the program by pressing any key with a right click
	//	if (key == "z")
	//	{
	//		std::cout << "Control + z held. ";
	//		this->GetDefaultRenderer()->RemoveActor(selectedActor);
	//		count = count - 1;
	//		if (count == 0 || count == 1) {
	//			source_count--;
	//		}
	//		if (count == 2) {
	//			source_count--;
	//			thirdPickConfirmed = true;  //this needs a confirmation from user to swtich renderer in the future
	//		}
	//		if (count == 3 || count == 4) {
	//			target_count--;
	//		}
	//		if (count == 5) {
	//			target_count--;
	//			sixthPickConfirmed = true; //this needs a confirmation from user
	//		}
	//		std::cout << "re-pick number  " << count << std::endl;
	//		std::cout << "source number  " << source_count << std::endl;
	//		std::cout << "target number  " << target_count << std::endl;
	//	}
	//}

	vtkInteractorStyleTrackballCamera::OnKeyPress();
}
vtkStandardNewMacro(PointSelection);