#include "PointStorage.h"
using namespace std;


	//constructor
	pointStorage::pointStorage(int size) {
		currpos = 0;
		this->size = size;
		points.reserve(size);
	}

	//add a new point to the vector
	void pointStorage::add(vtkIdType pid, double dist) {
		points.push_back(point(pid, dist));
		disttot += dist;
		currpos++;
	}

	point pointStorage::getpoint(int id) {
		return points[id];
	}

	point *pointStorage::iterate() {
		currpos++;
		if ((unsigned int)currpos > points.size()) {
			currpos = 0;
			return nullptr;
		}
		else {
			return &getpoint(currpos - 1);
		}
	}

	void pointStorage::setPos(int pos) {
		currpos = pos;
	}

	double pointStorage::getAvgDist() {
		return (disttot / points.size());
	}
