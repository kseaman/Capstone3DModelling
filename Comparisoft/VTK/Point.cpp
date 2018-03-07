#include "Point.h"
#include <cstring>


	//class constructor
	point::point(vtkIdType i, double dist) {
		id = i;
		distance = dist;
	}

	//return id
	vtkIdType point::getId() {
		return id;
	}

	//return distance
	double point::getDistance() {
		return distance;
	}
