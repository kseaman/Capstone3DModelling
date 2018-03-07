#pragma once
#include <vtkPolyData.h>

class point {
	vtkIdType id;
	double distance;

public:
	point(vtkIdType i, double dist);
	vtkIdType getId();
	double getDistance();
};