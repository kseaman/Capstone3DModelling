#include "PointStorage.h"
using namespace std;

class pointStore {

//store all of the points and the information about them
private: 
	class point {
		double pos[3];
		double nearestPos[3];
		double distance;

	public:
		//class constructor
		point(double pointpos[3], double near[3], double dist) {
			memcpy(pos, pointpos, sizeof(pos));
			memcpy(nearestPos, near, sizeof(nearestPos));
			distance = dist;
		}

		//return the point position
		double* getPos() {
			return pos;
		}

		//return nearest position
		double* getNearestPos() {
			return nearestPos;
		}

		//return distance
		double getDistance() {
			return distance;
		}
	};

	//set member variables
	int currpos;
	int size;
	vector<point> points;

public:

	//constructor
	pointStore(int size) {
		currpos = 0;
		this->size = size;
		points.reserve(size);
	}

	//add a new point to the vector
	void add(double pointpos[3], double near[3], double dist) {
		points.push_back(point(pointpos, near, dist));
		currpos++;
	}
};