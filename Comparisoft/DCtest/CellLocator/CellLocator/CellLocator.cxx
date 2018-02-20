#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCellLocator.h>
#include <vtkMath.h>
#include <stdio.h>
#include <math.h>



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

	// Find the squared distance between the points.
	double squaredDistance = vtkMath::Distance2BetweenPoints(p0, p1);

	// Take the square root to get the Euclidean distance between the points.
	double distance = sqrt(squaredDistance);

	// Output the results.
	std::cout << "SquaredDistance = " << squaredDistance << std::endl;
	std::cout << "Distance = " << distance << std::endl;

  char end;

  std::cin >> end;
  
  
  return EXIT_SUCCESS;
}
