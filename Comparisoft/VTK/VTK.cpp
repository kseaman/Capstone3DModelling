#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkTextWidget.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkCoordinate.h>
#include <vtkCommand.h>
#include "VTK.h"
#include "PointSelection.h"
#include "Align.h"
#include "PointStorage.h"

#include <cstdio>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

//VTK code goes here. It is now a function, and is called with the file paths.
int VTKmain(char* filePathSource, char* filePathTarget, std::string filename, char *camera, std::string report_name)
{

    if (filePathSource == NULL || filePathTarget == NULL) {
        printf("Please select both files first.\n");
        return 0;
    }

    // File 1
    vtkSmartPointer<vtkSTLReader> reader1 =
            vtkSmartPointer<vtkSTLReader>::New();
    reader1->SetFileName(filePathSource);
    reader1->Update();
    vtkSmartPointer<vtkTriangleFilter> triangleFilter1 =
            vtkSmartPointer<vtkTriangleFilter>::New();
    triangleFilter1->SetInputConnection(reader1->GetOutputPort());
    triangleFilter1->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper1 =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper1->SetInputConnection(triangleFilter1->GetOutputPort());
    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
    actor1->SetMapper(mapper1);

    // File 2
    vtkSmartPointer<vtkSTLReader> reader2 =
            vtkSmartPointer<vtkSTLReader>::New();
    reader2->SetFileName(filePathTarget);
    reader2->Update();
    vtkSmartPointer<vtkTriangleFilter> triangleFilter2 =
            vtkSmartPointer<vtkTriangleFilter>::New();
    triangleFilter2->SetInputConnection(reader2->GetOutputPort());
    triangleFilter2->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper2 =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2->SetInputConnection(triangleFilter2->GetOutputPort());
    vtkSmartPointer<vtkActor> actor2 =
            vtkSmartPointer<vtkActor>::New();
    actor2->SetMapper(mapper2);

    // Define viewport ranges
    double source_pane[4] = {0, 0.5, 0.5, 1};
    double target_pane[4] = {0.5, 0.5, 1, 1};
    double comparison_pane[4] = {0, 0, 0.5, 0.5};
    double heatmap_pane[4] = {0.5, 0, 1, 0.5};

    // Renderers
    vtkSmartPointer<vtkRenderer> renderer1 =
            vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> renderer2 =
            vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> renderer3 =
            vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> renderer4 =
            vtkSmartPointer<vtkRenderer>::New();

    /* Set-up Source Pane */
    renderer1->AddActor(actor1);
    renderer1->SetBackground(.72, .74, .73);
    renderer1->SetViewport(source_pane);
    renderer1->ResetCamera();

    // Set up target pane
    renderer2->AddActor(actor2);
    renderer2->SetBackground(.55, .56, .55);
    renderer2->SetViewport(target_pane);
    renderer2->ResetCamera();
    
    // Setup the text and add it to the renderer 1 and 2
    vtkSmartPointer<vtkTextActor> textActor =
            vtkSmartPointer<vtkTextActor>::New();
    textActor->SetInput ( "Source" );
    textActor->SetPosition2 ( 10, 40 );
    textActor->GetTextProperty()->SetFontSize ( 34 );
    textActor->GetTextProperty()->SetColor ( 0.71, 0.95, 0.35 );
    renderer1->AddActor2D ( textActor );
    vtkSmartPointer<vtkTextActor> textActor2 =
            vtkSmartPointer<vtkTextActor>::New();
    textActor2->SetInput ( "Target" );
    textActor2->SetPosition2 ( 10, 40 );
    textActor2->GetTextProperty()->SetFontSize ( 34 );
    textActor2->GetTextProperty()->SetColor ( 0.71, 0.95, 0.35 );
    renderer2->AddActor2D ( textActor2 );

    // Set-up combined Comparison Pane
    renderer3->SetBackground(.35, .36, .35);
    renderer3->SetViewport(comparison_pane);
    renderer3->ResetCamera();

    /* Set-up combined Heat Map display pane */
    renderer4->SetBackground(.24, .24, .24);
    renderer4->SetViewport(heatmap_pane);
    renderer4->ResetCamera();

    /* If the camera is set up for matching files, same camera for both renderers to ensure simultaneous interaction*/
    if (strcmp(camera, "0") == 0) {
        renderer2->SetActiveCamera(renderer1->GetActiveCamera());
    }

    // Create one render window and one interactor for each pane
    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(800, 800);
    renderWindow->AddRenderer(renderer1);
    renderWindow->AddRenderer(renderer2);
    renderWindow->AddRenderer(renderer3);
    renderWindow->AddRenderer(renderer4);

    // Create render window interactor, set render window
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<PointSelection> style =
            vtkSmartPointer<PointSelection>::New();
    style->SetDefaultRenderer(renderer1);
    style->Data = triangleFilter1->GetOutput();
    style->filePathSource = filePathSource;
    style->filePathTarget = filePathTarget;
    renderWindowInteractor->SetInteractorStyle(style);

    vtkSmartPointer<vtkAxesActor> axes =
            vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> widget =
            vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    widget->SetOrientationMarker(axes);
    widget->SetInteractor(renderWindowInteractor);
    widget->SetEnabled(1);
    widget->InteractiveOn();

    char file[100];
    strcpy(file, filename.c_str());
    sprintf(PointSelection::screenshot, "%s", file);

    renderWindow->Render();
    renderWindow->SetWindowName("Perfit Compare");
    renderWindowInteractor->Start();

	ofstream report_output;
	report_output.open(report_name, std::ofstream::app);

	for (int i = 2; i < screenshot_count; i++) {
		char additional_screenshot[100];
		sprintf(additional_screenshot, "%s%s%i%s", filename.c_str(), "_", i, ".png");

		report_output << "\t\t<p></p>\n";
		report_output << "\t\t<center><img align=\"middle\" src=\"";
		report_output << additional_screenshot;
		report_output << "\" alt=\"Screenshot" << i << "\"></center>";

		report_output << "\t</body>\n";
	}

	report_output << "</html>\n";
    report_output.close();

    return EXIT_SUCCESS;
}