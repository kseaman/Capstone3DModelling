#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCellLocator.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkTriangle.h>
#include <vtkMath.h>
#include <stdio.h>
#include <math.h>

void triangleProjection(double *p0, double *p1, double *p2, double *p3, bool &isInside, double &dist, double* closestPoint) {

	// Create a plane
	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin(p1[0], p1[1], p1[2]);

	//compute the normal
	double normal[3];
	vtkTriangle::ComputeNormal(p1, p2, p3, normal);

	plane->SetNormal(normal[0], normal[1], normal[2]);

	//project point onto plane
	plane->ProjectPoint(p0, p1, normal, closestPoint);

	// Find the squared distance between the points.
	double squaredDistance = vtkMath::Distance2BetweenPoints(p0, closestPoint);

	// Take the square root to get the Euclidean distance between the points.
	dist = sqrt(squaredDistance);

}



int main(int, char *[])
{
	//double rad = 1.0;
	//double expectedDist = 0.0;
 // vtkSmartPointer<vtkSphereSource> sphereSource = 
 //   vtkSmartPointer<vtkSphereSource>::New();
 // sphereSource->SetCenter(0.0, 0.0, 0.0);
 // sphereSource->SetRadius(rad);
 // sphereSource->Update();
 // 
 // // Create the tree
 // vtkSmartPointer<vtkCellLocator> cellLocator = 
 //   vtkSmartPointer<vtkCellLocator>::New();
 // cellLocator->SetDataSet(sphereSource->GetOutput());
 // cellLocator->BuildLocator();
 // 
 // double testPoint[3] = {1.0, 1.0, 1.0};
 // 
 // //Find the closest points to TestPoint
 // double closestPoint[3];//the coordinates of the closest point will be returned here
 // double closestPointDist2; //the squared distance to the closest point will be returned here
 // vtkIdType cellId; //the cell id of the cell containing the closest point will be returned here
 // int subId; //this is rarely used (in triangle strips only, I believe)
 // cellLocator->FindClosestPoint(testPoint, closestPoint, cellId, subId, closestPointDist2);
 // 
 // std::cout << "Coordinates of closest point: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
 // std::cout << "Distance to closest point: " << sqrt(closestPointDist2) << std::endl;
 // std::cout << "Error: " << (expectedDist - sqrt(closestPointDist2)) << std::endl;
 // std::cout << "Error%: " << ((expectedDist - sqrt(closestPointDist2))/ expectedDist)*100 << std::endl;
 // std::cout << "Squared distance to closest point: " << closestPointDist2 << std::endl;
 // std::cout << "CellId: " << cellId << std::endl;
 // std::cout << "Enter anything to close.";

	double p0[3] = { 1.0, 0.5, 1.0 };
	double p1[3] = { 0.0, 0.0, 0.0 };
	double p2[3] = { 2.0, 2.0, 0.0 };
	double p3[3] = { 2.0, 0.0, 0.0 };

	bool inside;
	double distance;
	double closestPoint[3];

	

	// Output the results.
	std::cout << "Distance = " << distance << std::endl;

  char end;

  std::cin >> end;
  
  
  return EXIT_SUCCESS;
}
