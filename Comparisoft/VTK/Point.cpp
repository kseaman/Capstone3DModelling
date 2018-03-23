#include "Point.h"
#include <cstring>


	//class constructor
	point::point(vtkIdType i, float dist) {
		id = i;
		distance = dist;
	}

	//return id
	vtkIdType point::getId() {
		return id;
	}

	//return distance
	float point::getDistance() {
		return distance;
	}
