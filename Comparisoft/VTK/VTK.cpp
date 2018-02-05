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

#include <cstdio>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>


//VTK code goes here. It is now a function, and is called with the file paths.
int VTKmain(char* filePathReference, char* filePathProduction)
{


    if (filePathReference == NULL || filePathProduction == NULL) {
        printf("Please select both files first.\n");
        return 0;
    }

    //File 1
    vtkSmartPointer<vtkSTLReader> reader1 =
            vtkSmartPointer<vtkSTLReader>::New();

    //reader1->SetFileName(utf8_encode(filePathReferance).c_str());
    reader1->SetFileName(filePathReference);
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



    //file 2
    vtkSmartPointer<vtkSTLReader> reader2 =
            vtkSmartPointer<vtkSTLReader>::New();
    reader2->SetFileName(filePathProduction);
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


    /* Define viewport ranges */
    double reference_pane[4] = {0, 0.5, 0.5, 1};
    double production_pane[4] = {0.5, 0.5, 1, 1};
    double comparison_pane[4] = {0, 0, 1, 0.5};


    //renderer
    vtkSmartPointer<vtkRenderer> renderer1 =
            vtkSmartPointer<vtkRenderer>::New();


    vtkSmartPointer<vtkRenderer> renderer2 =
            vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderer> renderer3 =
            vtkSmartPointer<vtkRenderer>::New();

    /* Set-up Reference Pane */
    renderer1->AddActor(actor1);
    renderer1->SetBackground(.5, .5, .6);
    renderer1->SetViewport(reference_pane);
    renderer1->ResetCamera();

    /* Set-up Production Pane */
    renderer2->AddActor(actor2);
    renderer2->SetBackground(.5, .6, .5);
    renderer2->SetViewport(production_pane);
    renderer2->ResetCamera();

    
    // Setup the text and add it to the renderer 1 and 2
    vtkSmartPointer<vtkTextActor> textActor =
            vtkSmartPointer<vtkTextActor>::New();
    textActor->SetInput ( "Reference" );
    textActor->SetPosition2 ( 10, 40 );
    textActor->GetTextProperty()->SetFontSize ( 24 );
    textActor->GetTextProperty()->SetColor ( 0.0, 1.0, 0.0 );
    renderer1->AddActor2D ( textActor );

    vtkSmartPointer<vtkTextActor> textActor2 =
            vtkSmartPointer<vtkTextActor>::New();
    textActor2->SetInput ( "Production" );
    textActor2->SetPosition2 ( 10, 40 );
    textActor2->GetTextProperty()->SetFontSize ( 24 );
    textActor2->GetTextProperty()->SetColor ( 0.0, 1.0, 0.0 );
    renderer2->AddActor2D ( textActor2 );



    /* Set-up combined Comparison Pane */
    renderer3->SetBackground(.5, .7, .8);
    renderer3->SetViewport(comparison_pane);
    renderer3->ResetCamera();


    //set the same camera for both renderers to ensure simultaneous interaction
    renderer2->SetActiveCamera(renderer1->GetActiveCamera());

    /* Create one render window and one interactor for each pane */
    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();

    renderWindow->SetSize(800, 800);
    renderWindow->AddRenderer(renderer1);
    renderWindow->AddRenderer(renderer2);
    renderWindow->AddRenderer(renderer3);

    //create render window interactor, set render window
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    //Set point selection style to that defined in MouseInteractorStyle.h
    vtkSmartPointer<PointSelection> style =
            vtkSmartPointer<PointSelection>::New();
    std::cout << "pick on renderer 1 " << std::endl;
    style->SetDefaultRenderer(renderer1);
    style->Data = triangleFilter1->GetOutput();
    style->filePathRef = filePathReference;
    style->filePathProd = filePathProduction;
    renderWindowInteractor->SetInteractorStyle(style);



    //Once all the click work is done, this will show the aligned models
    vtkSmartPointer<vtkAxesActor> axes =
            vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> widget =
            vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    widget->SetOrientationMarker(axes);
    widget->SetInteractor(renderWindowInteractor);
    widget->SetEnabled(1);
    widget->InteractiveOn();


    renderWindow->Render();
    renderWindow->SetWindowName("Comparisoft");
    renderWindowInteractor->Start();


    return EXIT_SUCCESS;
}