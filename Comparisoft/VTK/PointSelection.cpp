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

/**
	@brief Alter the inherited OnLeftButtonDown() of
	vtkInteractorStyleTrackballCamera to be compatible with our intended use.
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

	if(picker->GetCellId() == -1){
		std::cout << "Invalid input, try again! cell id is: " << picker->GetCellId() << std::endl;
	}

	//making sure the pick is not off image (no cellData is cellId =1 )
	if(picker->GetCellId() != -1)
	{

		std::cout << "Valid input selected: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

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

		vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();

		//set both mapper dataset Data and selection consisting selected node as input for extractSelection
		extractSelection->SetInputData(0, this->Data);
		extractSelection->SetInputData(1, selection);
		extractSelection->Update();

        vtkActor **array = new vtkActor* [6];
        array[count]= vtkActor::New();

		//setting mapper and actor here ensures selection remain highlighted
        selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        selectedActor = array[count];
		
		vtkSmartPointer<vtkUnstructuredGrid> selected =
				vtkSmartPointer<vtkUnstructuredGrid>::New();
		selected->ShallowCopy(extractSelection->GetOutput());

		selectedMapper->SetInputData(selected);
		selectedActor->SetMapper(selectedMapper);
		selectedActor->GetProperty()->EdgeVisibilityOn();
		selectedActor->GetProperty()->SetLineWidth(100);
		
		count++;
		//process 6 picks colour, point 1,3,5 from renderer 1, point 2,4,6 from renderer 2
        if(count == 1 || count == 2){
            selectedActor->GetProperty()->SetEdgeColor(1,0,0);
        }
        if(count == 3 || count == 4){
            selectedActor->GetProperty()->SetEdgeColor(0,1,0); //colour code the 2nd pick in each renderer to blue
        }
        if(count == 5 || count == 6){
            selectedActor->GetProperty()->SetEdgeColor(0,0,1);//colour code the 3rd pick in each renderer to red
        }


		if(count==1 || count == 3 || count== 5){

			this->GetDefaultRenderer()->AddActor(selectedActor);
			source_coordinates[source_count] = {picked[0], picked[1], picked[2]}; //stores source coordinates
            std::cout << "Source Value stored: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
            std::cout << "Point on R Pane (x, y, z): " << source_coordinates[source_count].x_val << " "
                      << source_coordinates[source_count].y_val << " " << source_coordinates[source_count].z_val << std::endl;
			source_count++;
            std::cout << count << " pick completed, "  <<  source_count << " source coordinates stored " << std::endl;

            std::cout << std::endl;

		}

		else if(count== 2 || count == 4 || count ==6)
		{
			this->GetDefaultRenderer()->AddActor(selectedActor);
			target_coordinates[target_count] = {picked[0], picked[1], picked[2]};
			std::cout << "Target Value stored: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

			std::cout << "Point on P Pane (x, y, z): " << target_coordinates[target_count].x_val << " "
					  << target_coordinates[target_count].y_val << " " << target_coordinates[target_count].z_val << std::endl;

			target_count++;
			std::cout << count << " pick completed, "  <<  target_count << " target coordinates stored " << std::endl;
			std::cout << std::endl;
		}

		//store picks after the end of selection
		if(count==6 ){
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


			is_completed=true;
			if(is_completed){
				//change default renderer to renderer 3, such that renderer 3 can be accessed
				vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
				vtkRenderer* nextRenderer = (vtkRenderer*)panes->GetItemAsObject(2);
				this->SetDefaultRenderer(nextRenderer);

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
			}
		}
	}
	//forward events
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();

}
void PointSelection:: OnKeyPress() {

    controlPressed = this->GetInteractor()->GetControlKey();

    // Get the keypress
    vtkRenderWindowInteractor *rwi = this->Interactor;
    std::string key = rwi->GetKeySym();


    // Output the key that was pressed
    std::cout << "Pressed " << key << std::endl;

    // Handle different keys
    if (key == "z") {
        zPressed = true;
    }
    if(controlPressed && zPressed){

        std::cout << "The control + z key was pressed." << std::endl;
        std::cout << "Remove previous point " << count << std::endl;
        this->GetDefaultRenderer()->RemoveActor(selectedActor);

        if (count == 1 || count == 3 || count == 5) {
            source_count--; //clear either pick 1, 3, 5
        }

        if (count == 2 || count == 4 || count == 6) {
            target_count--; //clear pick 2, 4, 6
        }

        std::cout << "source number  " << source_count << std::endl;
        std::cout << "target number  " << target_count << std::endl;
        count = count - 1;
        controlPressed = false;
        zPressed = false;

    }

    if(key == "e"){
        this->GetInteractor()->ExitCallback();
    }
    if(key == "b")
    {
        keyBPressed = true;
        std::cout << "The key 3 was pressed." << std::endl;
        if(keyBPressed){
            //change default renderer to renderer 3
            vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
            vtkRenderer* nextRenderer = (vtkRenderer*)panes->GetItemAsObject(2);
            this->SetDefaultRenderer(nextRenderer);


        }
    }

    if(key == "2")
    {
        key2Pressed = true;
        std::cout << "The key 2 was pressed." << std::endl;
        if(key2Pressed){
            //change default renderer to renderer 2
            vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
            vtkRenderer* nextRenderer = (vtkRenderer*)panes->GetItemAsObject(1);
            this->SetDefaultRenderer(nextRenderer);


            //change data into new renderer's data set
            vtkActorCollection* actors = nextRenderer->GetActors();
            vtkActor* Actor = (vtkActor*) actors->GetItemAsObject(0);
            vtkDataSetMapper* mapper = (vtkDataSetMapper*)Actor->GetMapper();
            vtkPolyData* triangleFilter2;
            triangleFilter2 = dynamic_cast<vtkPolyData *>(mapper->GetInputAsDataSet());
            Data=triangleFilter2;
            key2Pressed = false;
        }
    }


    if(key == "1")
    {
        key1Pressed = true;
        std::cout << "The key 1 was pressed." << std::endl;
        if(key1Pressed){
            //change default renderer to renderer 1
            vtkRenderer* nextRenderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
            this->SetDefaultRenderer(nextRenderer);


            //change data into new renderer's data set
            vtkActorCollection* actors = nextRenderer->GetActors();
            vtkActor* Actor = (vtkActor*) actors->GetItemAsObject(0);
            vtkDataSetMapper* mapper = (vtkDataSetMapper*)Actor->GetMapper();
            vtkPolyData* triangleFilter1;
            triangleFilter1 = dynamic_cast<vtkPolyData *>(mapper->GetInputAsDataSet());
            Data=triangleFilter1;
            key1Pressed = false;
        }
    }




    // Forward events
    vtkInteractorStyleTrackballCamera::OnKeyPress();
}


vtkStandardNewMacro(PointSelection);