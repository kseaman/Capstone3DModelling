#pragma once
#include <vtkPolyData.h>

class point {
	vtkIdType id;
	float distance;

public:
	point(vtkIdType i, float dist);
	vtkIdType getId();
	float getDistance();
};