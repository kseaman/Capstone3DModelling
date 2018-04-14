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
@author 	Dana Klamut, Zifang Jiang, Emerson Kirby
@details	This file handles the point selection on the data sets.
Adapted from: https://www.vtk.org/Wiki/VTK/Examples/Cxx/Interaction/PointPicker
*/
/******************************************************************************/


#include "PointSelection.h"
#include "Align.h"
#include "vtkActor.h"
#include <vtkTextProperty.h>
char PointSelection::screenshot[500] = "";
vtkRenderer* combinedPane;
vtkRenderer* heatMapPane;

// Switch between renderers. Used for highlighting points
void PointSelection::SwitchRenderer()
{
	vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
	if (isSourceRenderer) {
		this->SetDefaultRenderer((vtkRenderer*)panes->GetItemAsObject(1));
		isSourceRenderer = false;
	}
	else {
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

vtkSmartPointer<vtkActor> PointSelection::MarkPoint(vtkSmartPointer<vtkCellPicker> p) {
	vtkSmartPointer<vtkIdTypeArray> ids =
		vtkSmartPointer<vtkIdTypeArray>::New();
	ids->SetNumberOfComponents(1);
	ids->InsertNextValue(p->GetCellId());

	// Storing id into node
	vtkSmartPointer<vtkSelectionNode> selectionNode =
		vtkSmartPointer<vtkSelectionNode>::New();
	selectionNode->SetFieldType(vtkSelectionNode::CELL);
	selectionNode->SetContentType(vtkSelectionNode::INDICES);
	selectionNode->SetSelectionList(ids);

	// Node stored into selection
	vtkSmartPointer<vtkSelection> selection =
		vtkSmartPointer<vtkSelection>::New();
	selection->AddNode(selectionNode);

	// Set both mapper dataset Data and selection consisting selected node as input for extractSelection
	vtkSmartPointer<vtkExtractSelection> extractSelection =
		vtkSmartPointer<vtkExtractSelection>::New();
	extractSelection->SetInputData(0, this->Data);
	extractSelection->SetInputData(1, selection);
	extractSelection->Update();

	vtkSmartPointer<vtkUnstructuredGrid> selected =
		vtkSmartPointer<vtkUnstructuredGrid>::New();
	selected->ShallowCopy(extractSelection->GetOutput());

	// Setting mapper and actor here ensures selection remain highlighted
	selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
	selectedActor = vtkSmartPointer<vtkActor>::New();

	selectedMapper->SetInputData(selected);
	selectedActor->SetMapper(selectedMapper);
	selectedActor->GetProperty()->EdgeVisibilityOn();
	selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
	selectedActor->GetProperty()->SetLineWidth(100);

	// Store the just added actor for later removal
	markedPoints.push_back(selectedActor);

	return selectedActor;
}

/**
@brief Alter the inherited OnRightButtonDown() of
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

	// Making sure the pick is not off the actor and not above six pix
	if (picker->GetCellId() != -1 && count < 6 && count >=0)
	{
		// Find the source and target panes and store them
		//vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
		vtkRenderer* sourceRenderer = (vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(0);
		vtkRenderer* targetRenderer = (vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(1);
		
		vtkSmartPointer<vtkActor> markedPoint =
			vtkSmartPointer<vtkActor>::New();
		markedPoint = MarkPoint(picker);

		if ((source_count < 3) && (count % 2 == 0) && (this->GetDefaultRenderer() == sourceRenderer)) {
			switch (source_count) {
				case 0: {
					markedPoint->GetProperty()->SetEdgeColor(1, 0, 0);
                    targetRenderer->SetBackground(0.48, 0.62, 0.45); //change to green
					sourceRenderer->SetBackground(.72, .74, .73);    //remove highlights
					break;
				}
				case 1: {
					markedPoint->GetProperty()->SetEdgeColor(0, 1, 0);
                    targetRenderer->SetBackground(0.48, 0.62, 0.45);
                    sourceRenderer->SetBackground(.72, .74, .73);
					break;
				}
				case 2: {
					markedPoint->GetProperty()->SetEdgeColor(0, 0, 1);
                    targetRenderer->SetBackground(0.48, 0.62, 0.45);
                    sourceRenderer->SetBackground(.72, .74, .73);
					break;
				}
			}

			//Only on the source renderer
			this->GetDefaultRenderer()->AddActor(markedPoint);
            this->Interactor->GetRenderWindow()->Render();

			SwitchRenderer();
			source_coordinates[source_count] = { picked[0], picked[1], picked[2] }; //stores source coordinates
			source_count++;
			count++;
		}
		else if ((target_count < 3) && (count % 2 != 0) && (this->GetDefaultRenderer() == targetRenderer)) {
			switch (target_count) {
			case 0: {
				markedPoint->GetProperty()->SetEdgeColor(1, 0, 0);
                sourceRenderer->SetBackground(0.48, 0.62, 0.45);
                targetRenderer->SetBackground(.55, .56, .55);
                break;
			}
			case 1: {
				markedPoint->GetProperty()->SetEdgeColor(0, 1, 0);
                sourceRenderer->SetBackground(0.48, 0.62, 0.45);
                targetRenderer->SetBackground(.55, .56, .55);
                break;
			}
			case 2: {
				markedPoint->GetProperty()->SetEdgeColor(0, 0, 1);
                sourceRenderer->SetBackground(.72, .74, .73);
                targetRenderer->SetBackground(.55, .56, .55);
                break;
			}

			}
			//Only on the target renderer
			this->GetDefaultRenderer()->AddActor(markedPoint);
            this->Interactor->GetRenderWindow()->Render();

			SwitchRenderer();
			target_coordinates[target_count] = {picked[0], picked[1], picked[2]}; //stores target coordinates
			target_count++;
			count++;
		}
		
	}
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

void PointSelection::OnLeftButtonDown() {
	// This is overridden so as to allow user to interact with locked pane
	int x = this->Interactor->GetEventPosition()[0];
	int y = this->Interactor->GetEventPosition()[1];
	vtkRenderer* pokedRen = this->GetInteractor()->FindPokedRenderer(x, y);
	if (pokedRen == (vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(2)) {
		// If they pick the bottom panel
		this->SetDefaultRenderer((vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(2));
	}
	else if (pokedRen == (vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(3)) {
		// Bottom right panel is selected
		this->SetDefaultRenderer((vtkRenderer*)this->Interactor->GetRenderWindow()->GetRenderers()->GetItemAsObject(3));
	}
	else if (!(pokedRen == this->GetDefaultRenderer())) {
		// Otherwise switch through the bottom panel
		SwitchRenderer();
	}
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

// Implementing hot keys
void PointSelection::OnKeyPress() {
	vtkRenderWindowInteractor *rwi = this->Interactor;
	std::string key = rwi->GetKeySym();
	
	vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
	vtkRenderer* renderer1 = (vtkRenderer*)panes->GetItemAsObject(0);
	vtkRenderer* renderer2 = (vtkRenderer*)panes->GetItemAsObject(1);

	// ENTER    ===== begin alignment
	if (key == "Return" && count == 6) {
		Align bottomPanel;
		bottomPanel.cam = this->cam;
		bottomPanel.filePathTarget = this->filePathTarget;
		bottomPanel.filePathSource = this->filePathSource;

		//Get renderer for bottom viewpoint (it is the third renderer in the collection)
		vtkRendererCollection* panes = this->Interactor->GetRenderWindow()->GetRenderers();
		vtkRenderer* combinedPane = (vtkRenderer*)panes->GetItemAsObject(2);

		//Remove overlapping textActors
		combinedPane->RemoveAllViewProps();

		//Show alignment in progress message before alignment
        vtkSmartPointer<vtkTextActor> textActor =
                vtkSmartPointer<vtkTextActor>::New();
        textActor->SetInput ( "Alignment in progress" );
        textActor->SetPosition ( 10, 10 );
        textActor->GetTextProperty()->SetFontSize ( 34 );
        textActor->GetTextProperty()->SetColor (0.71, 0.95, 0.35);
        combinedPane->AddActor2D ( textActor );
        this->Interactor->GetRenderWindow()->Render();

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

		//Add the transformed actors to , which is returned by bottompanel.alignmodels
		bottomPanel.source_actor = vtkSmartPointer<vtkActor>::New();
		bottomPanel.target_actor = vtkSmartPointer<vtkActor>::New();

		bottomPanel.AlignModels();

		combinedPane->AddActor(bottomPanel.target_actor);
		combinedPane->AddActor(bottomPanel.source_actor);
        //Show alignment complete after alignment
        textActor->SetInput ( "Alignment complete" );
        combinedPane->AddActor(textActor);
		combinedPane->ResetCamera();
		this->Interactor->GetRenderWindow()->Render();

		/* Set-up heat map following alignment */
		heat_map.sourceObj = bottomPanel.source_obj;
		heat_map.targetObj = bottomPanel.target_obj;
		heat_map.clevel = clevel;
		heat_map.ebound = ebound;
		heat_map.eunit = eunit;
		heat_map.sourceObjActor = vtkSmartPointer<vtkActor>::New();
		heat_map.targetObjActor = vtkSmartPointer<vtkActor>::New();

		/* Get renderer for bottom right viewpoint (it is the 4th renderer in the collection) */
		heatMapPane = (vtkRenderer *)panes->GetItemAsObject(3);

		// remove any previous actors if the algoritm is run multiple times
		heatMapPane->RemoveAllViewProps();

		vtkSmartPointer<vtkTextActor> textActor2 =
				vtkSmartPointer<vtkTextActor>::New();
		textActor2->SetPosition ( 10, 10 );
		textActor2->GetTextProperty()->SetFontSize ( 34 );
		textActor2->GetTextProperty()->SetColor (0.71, 0.95, 0.35);
		textActor2->SetInput ( "Heatmap Calculation in progress" );
		heatMapPane->AddActor(textActor2);
		heatMapPane->ResetCamera();
		this->Interactor->GetRenderWindow()->Render();

		//distance calculation
		heat_map.DisplayHeatMap();

		heatMapPane->AddActor(heat_map.sourceObjActor);
		heatMapPane->AddActor2D(heat_map.scalarBarS);
		heatMapPane->ResetCamera();
		heatmapIsSource = true;
		heatmapReady = true;

		//display source file heatmap message by default
		if (heatmapIsSource) {
			textActor2->SetInput ( "Source file heatmap" );
			heatMapPane->AddActor(textActor2);
			heatMapPane->ResetCamera();
			this->Interactor->GetRenderWindow()->Render();

		}
		this->Interactor->GetRenderWindow()->Render();

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
		char screenshot_1[500];
		sprintf(screenshot_1, "%s%s", PointSelection::screenshot, "_1.png");
		writer->SetFileName(screenshot_1);
		writer->SetInputConnection(windowToImageFilter->GetOutputPort());
		writer->Write();
	}

	// CTRL + L ===== toggle lock on target pane
	if (this->Interactor->GetControlKey() && key == "l") {
		if ((renderer2->GetActiveCamera()) == (renderer1->GetActiveCamera())) {
			// Lock the pane
			vtkSmartPointer<vtkCamera> lockedCam =
				vtkSmartPointer<vtkCamera>::New();
			lockedCam->SetPosition(renderer2->GetActiveCamera()->GetPosition());
			lockedCam->SetFocalPoint(renderer2->GetActiveCamera()->GetFocalPoint());
			lockedCam->SetViewUp(renderer2->GetActiveCamera()->GetViewUp());
			lockedCam->SetViewAngle(renderer2->GetActiveCamera()->GetViewAngle());

			renderer2->SetActiveCamera(lockedCam);
			renderer2->ResetCamera();
		}
		else {
			// Unlock the pane
			renderer2->SetActiveCamera(renderer1->GetActiveCamera());
			renderer2->ResetCamera();
		}
	}

	// C ===== remove all points
	if (key == "c") {
		std::vector<vtkSmartPointer<vtkActor> >::iterator itr;
		for (itr = markedPoints.begin(); itr != markedPoints.end(); ++itr) {
			renderer1->RemoveActor(*itr);
			renderer2->RemoveActor(*itr);
		}
		markedPoints.clear();
		count = 0;
		source_count = 0;
		target_count = 0;
		renderer1->SetBackground(0.48, 0.62, 0.45); //highlight background color dark green to start selection
	}

	// S ===== switch heatmap
	if (key == "s") {
		if (heatmapReady) {
			heatMapPane = (vtkRenderer *)panes->GetItemAsObject(3);
			heatMapPane->RemoveAllViewProps();
			if (heatmapIsSource) {
				//switch the message when "s" is triggered in keypress
				vtkSmartPointer<vtkTextActor> textActor =
						vtkSmartPointer<vtkTextActor>::New();
				textActor->SetPosition ( 10, 10 );
				textActor->GetTextProperty()->SetFontSize ( 34 );
				textActor->GetTextProperty()->SetColor (0.71, 0.95, 0.35);
				textActor->SetInput ( "Target file heatmap" );
				heatMapPane->AddActor(textActor);
				heatMapPane->ResetCamera();
				this->Interactor->GetRenderWindow()->Render();

				heatMapPane->AddActor(heat_map.targetObjActor);
				heatMapPane->AddActor2D(heat_map.scalarBarT);
				heatMapPane->ResetCamera();
				heatmapIsSource = false;
			}
			else {
				vtkSmartPointer<vtkTextActor> textActor =
						vtkSmartPointer<vtkTextActor>::New();
				textActor->SetPosition ( 10, 10 );
				textActor->GetTextProperty()->SetFontSize ( 34 );
				textActor->GetTextProperty()->SetColor (0.71, 0.95, 0.35);
				textActor->SetInput ( "Source file heatmap" );
				heatMapPane->AddActor(textActor);
				heatMapPane->ResetCamera();
				this->Interactor->GetRenderWindow()->Render();

				heatMapPane->AddActor(heat_map.sourceObjActor);
				heatMapPane->AddActor2D(heat_map.scalarBarS);
				heatMapPane->ResetCamera();
				heatmapIsSource = true;
			}
		}
	}

	// E ===== exit program
	if (key == "e") {
		this->GetInteractor()->ExitCallback();
	}

	// CTRL + Z ===== to remove selected points
	if (this->Interactor->GetControlKey() && key == "z") {
		vtkRenderer* toRemove;
		if (markedPoints.size() >= 1) {
			if (count % 2 != 0 && source_count > 0) {
				source_count--;
				count--;
				toRemove = renderer1;
			}
			else if (count % 2 == 0 && target_count > 0) {
				target_count--;
				count--;
				toRemove = renderer2;
			}
			toRemove->RemoveActor(markedPoints.back());
			markedPoints.pop_back();
			toRemove->Render();
		}
		renderer1->SetBackground(0.48, 0.62, 0.45); //highlight background color dark green
	}

	// CTRL + P ===== to take a screenshot to include in report
	if (this->Interactor->GetControlKey() && key == "p") {
		vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
				vtkSmartPointer<vtkWindowToImageFilter>::New();
		windowToImageFilter->SetInput(this->Interactor->GetRenderWindow());
		windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
		windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
		windowToImageFilter->Update();
		vtkSmartPointer<vtkPNGWriter> writer =
				vtkSmartPointer<vtkPNGWriter>::New();
		char screenshot_path[500];
		sprintf(screenshot_path, "%s%s%i%s", PointSelection::screenshot, "_", screenshot_count, ".png");
		writer->SetFileName(screenshot_path);
		writer->SetInputConnection(windowToImageFilter->GetOutputPort());
		writer->Write();

		screenshot_count++;
	}
	vtkInteractorStyleTrackballCamera::OnKeyPress();
}
vtkStandardNewMacro(PointSelection);