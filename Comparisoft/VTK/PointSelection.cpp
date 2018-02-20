//
// Created by Zifang Jiang on 2018-01-29.
//
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
/**
	@brief Alter the inherited OnLeftButtonDown() of
	vtkInteractorStyleTrackballCamera to be compatible with our intended use.
	@returns void
*/
void PointSelection::OnRightButtonDown()
{
    controlPressed = this->Interactor->GetControlKey();
    if(controlPressed){
        std::string key = this->Interactor->GetKeySym();  //need to be filled to start the program by pressing any key with a right click
        if( key == "z")
        {
            std::cout << "Control + z held. ";
            this->GetDefaultRenderer()->RemoveActor(selectedActor);
            count = count-1;
            if(count == 0 || count == 1){
				source_count--;
            }
            if(count == 2){
				source_count--;
                thirdPickConfirmed = true;  //this needs a confirmation from user to swtich renderer in the future
            }
            if(count == 3 || count == 4){
                target_count--;
            }
            if(count == 5){
				target_count--;
                sixthPickConfirmed = true; //this needs a confirmation from user
            }
            std::cout << "re-pick number  " << count << std:: endl;
            std::cout << "source number  " << source_count << std:: endl;
            std::cout << "target number  " << target_count << std:: endl;

        }
    }


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

		//setting mapper and actor here ensures selection remain highlighted
		selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		selectedActor = vtkSmartPointer<vtkActor>::New();
		
		vtkSmartPointer<vtkUnstructuredGrid> selected =
				vtkSmartPointer<vtkUnstructuredGrid>::New();
		selected->ShallowCopy(extractSelection->GetOutput());

		selectedMapper->SetInputData(selected);
		selectedActor->SetMapper(selectedMapper);
		selectedActor->GetProperty()->EdgeVisibilityOn();
		selectedActor->GetProperty()->SetEdgeColor(1,0,0);
		selectedActor->GetProperty()->SetLineWidth(100);
		
		count++;
		//process 6 picks, point 1,2,3 from renderer 1, point 4,5,6 from renderer 2
		if(count<3){
			//first renderer for the first three picks
			if(count==2){
				selectedActor->GetProperty()->SetEdgeColor(0,1,0); //colour code the 2nd pick to blue
			}
			this->GetDefaultRenderer()->AddActor(selectedActor);
			source_coordinates[source_count] = {picked[0], picked[1], picked[2]}; //stores source coordinates
            std::cout << "Source Value stored: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
            std::cout << "Point on R Pane (x, y, z): " << source_coordinates[source_count].x_val << " "
                      << source_coordinates[source_count].y_val << " " << source_coordinates[source_count].z_val << std::endl;
			source_count++;
            std::cout << count << " pick completed, "  <<  source_count << " source coordinates stored " << std::endl;

            std::cout << std::endl;
            std::cout <<  "new pick in renderer 1 awaits " << std::endl;


		}
			//special case for count==3, switch renderer for next input, but still keep selected coordinates into source
		else if (count==3){

			selectedActor->GetProperty()->SetEdgeColor(0,0,1);

			this->GetDefaultRenderer()->AddActor(selectedActor);
			source_coordinates[source_count] = {picked[0], picked[1], picked[2]};
			std::cout << "Source Value stored: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
			std::cout << "Point on R Pane (x, y, z): " << source_coordinates[source_count].x_val << " "
					  << source_coordinates[source_count].y_val << " " << source_coordinates[source_count].z_val << std::endl;
			source_count++;

			std::cout << count << " pick completed, "  <<  source_count << " source coordinates stored " << std::endl;
			std::cout << std::endl;
			std::cout << "new pick in renderer 2 awaits " << std::endl;
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




		}
		else if(count<=6)
		{   //for the 4,5,6th picks
			if(count==4){
				selectedActor->GetProperty()->SetEdgeColor(1,0,0); //colour code the 2nd pick to blue
			}
			if(count==5){
				selectedActor->GetProperty()->SetEdgeColor(0,1,0); //colour code the 2nd pick to blue
			}
			if(count==6){
				selectedActor->GetProperty()->SetEdgeColor(0,0,1); //colour code the 2nd pick to blue
			}

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
		if(count==6){
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

			}
		}
	}
	//forward events
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();

}

vtkStandardNewMacro(PointSelection);