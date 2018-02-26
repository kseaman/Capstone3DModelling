#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkCellLocator.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkTriangle.h>
#include <vtkMath.h>
#include <stdio.h>
#include <math.h>

/*Check if a point is in a triangle when projected onto the plane
	Arguments: point to project, points of triangle, whether point is inside triangle, distance from point to projected point,
	projected point
	Create a plane from the triangle, and project the point onto it, compute distance
	Then project the triangle onto a 2D plane, and project the point onto the same plane.
	Use the 2D points to compute the barycentric coordinates to determine if the point is in the triangle.
*/
void triangleProjection(double *p0, double *p1, double *p2, double *p3, bool &isInside, double &dist, double* projectedPoint) {

	// Create a plane
	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin(p1[0], p1[1], p1[2]);

	//compute the normal
	double normal[3];
	vtkTriangle::ComputeNormal(p1, p2, p3, normal);
	plane->SetNormal(normal[0], normal[1], normal[2]);

	//project point onto plane formed by the triangle
	plane->ProjectPoint(p0, p1, normal, projectedPoint);

	// Find the squared distance between the points.
	double squaredDistance = vtkMath::Distance2BetweenPoints(p0, projectedPoint);

	// Take the square root to get the Euclidean distance between the points.
	dist = sqrt(squaredDistance);

	//check if the point is inside the triangle
	//project the triangle onto 2d
	double p21[3], p22[3], p23[3];
	vtkTriangle::ProjectTo2D(p1, p2, p3, p21, p22, p23);

	//make sure the last points are 0
	p21[2] = 0;	p22[2] = 0;	p23[2] = 0;

	//create a new 2d plane
	vtkSmartPointer<vtkPlane> plane2 =
		vtkSmartPointer<vtkPlane>::New();
	plane2->SetOrigin(p21[0], p21[1], p21[2]);

	//compute the plane's normal
	double normal2[3];
	vtkTriangle::ComputeNormal(p21, p22, p23, normal2);
	plane2->SetNormal(normal2[0], normal2[1], normal2[2]);

	//project the projected point onto the 2d plane formed by the projected triangle
	double projectedPoint2[3];
	plane2->ProjectPoint(projectedPoint, p21, normal2, projectedPoint2);

	//compute the barycentric coordinates
	double barycoords[3];
	vtkTriangle::BarycentricCoords(projectedPoint2, p21, p22, p23, barycoords);

	//check if the point is inside the triangle
	if (barycoords[0] > 0 && barycoords[1] > 0 && barycoords[2] > 0) {
		isInside = true;
	}
}



int main(int, char *[])
{
	double rad = 3.0;
	double expectedDist = rad - sqrt(6.0);
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(rad);
  sphereSource->SetThetaResolution(10000);
  sphereSource->SetPhiResolution(10000);
  sphereSource->Update();
  
  // Create the tree
  vtkSmartPointer<vtkCellLocator> cellLocator = 
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(sphereSource->GetOutput());
  cellLocator->BuildLocator();

  //display the sphere
  vtkSmartPointer<vtkPolyDataMapper> mapper =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
	  vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
	  vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
	  vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
	  vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  //calculate distance
  double testPoint[3] = {1.0, 1.0, 2.0};
  
  //Find the closest points to TestPoint
  double closestPoint[3];//the coordinates of the closest point will be returned here
  double closestPointDist2; //the squared distance to the closest point will be returned here
  vtkIdType cellId; //the cell id of the cell containing the closest point will be returned here
  int subId; //this is rarely used (in triangle strips only, I believe)
  cellLocator->FindClosestPoint(testPoint, closestPoint, cellId, subId, closestPointDist2);
  
  std::cout << "Coordinates of closest point: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  std::cout << "Distance to closest point: " << sqrt(closestPointDist2) << std::endl;
  std::cout << "Error: " << (expectedDist - sqrt(closestPointDist2)) << std::endl;
  std::cout << "Error%: " << ((expectedDist - sqrt(closestPointDist2))/ expectedDist)*100 << std::endl;
  std::cout << "Squared distance to closest point: " << closestPointDist2 << std::endl;
  std::cout << "CellId: " << cellId << std::endl;
  std::cout << std::endl << std::endl << std::endl;
  //std::cout << "Enter anything to close.";

	double p0[3] = { 1.0, 0.5, 5.0 };
	double p1[3] = { 0.0, 0.0, 0.0 };
	double p2[3] = { 2.0, 2.0, 2.0 };
	double p3[3] = { 2.0, 0.0, 2.0 };
	expectedDist = 4.0;

	bool inside;
	double distance;
	//double closestPoint[3];

	triangleProjection(p0, p1, p2, p3, inside, distance, closestPoint);

	

	// Output the results.
	std::cout << "Inside = " << inside << std::endl;
	std::cout << "Distance = " << distance << std::endl;
	std::cout << "Closest Point = " << closestPoint[0] <<", " << closestPoint[1] << ", " << closestPoint[2] << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	//dist mesthod
	//create a plane
	vtkSmartPointer<vtkPlaneSource> plane =
		vtkSmartPointer<vtkPlaneSource>::New();
	plane->SetOrigin(p1);
	plane->SetPoint1(p2);
	plane->SetPoint2(p3);
	//int x = plane->GetXResolution();
	//int y = plane->GetYResolution();
	int x, y;
	plane->SetXResolution(100);
	plane->SetYResolution(100);
	plane->Update();
	//std::cout << "XRes: " << x << std::endl;
	//std::cout << "YRes: " << y << std::endl;

	//compute the normal
	//double normal[3];
	//vtkTriangle::ComputeNormal(p1, p2, p3, normal);
	//plane->SetNormal(normal[0], normal[1], normal[2]);

	vtkSmartPointer<vtkCellLocator> cellLocator2 =
		vtkSmartPointer<vtkCellLocator>::New();
	cellLocator2->SetDataSet(plane->GetOutput());
	cellLocator2->BuildLocator();

	//Find the closest points to TestPoint
	//double closestPoint[3];//the coordinates of the closest point will be returned here
	//double closestPointDist2; //the squared distance to the closest point will be returned here
	//vtkIdType cellId; //the cell id of the cell containing the closest point will be returned here
	//int subId; //this is rarely used (in triangle strips only, I believe)
	cellLocator2->FindClosestPoint(p0, closestPoint, cellId, subId, closestPointDist2);

	 std::cout << "Coordinates of closest point: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
	 std::cout << "Distance to closest point: " << sqrt(closestPointDist2) << std::endl;
	 std::cout << "Error: " << (expectedDist - sqrt(closestPointDist2)) << std::endl;
	 std::cout << "Error%: " << ((expectedDist - sqrt(closestPointDist2))/ expectedDist)*100 << std::endl;
	 std::cout << "Squared distance to closest point: " << closestPointDist2 << std::endl;
	 std::cout << "CellId: " << cellId << std::endl;

	//activate display

	renderWindow->Render();
	renderWindowInteractor->Start();

  char end;

  std::cin >> end;
  
  
  return EXIT_SUCCESS;
}
