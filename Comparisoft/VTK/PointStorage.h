#pragma once
#include <vector>

class pointStore {

private: 
	class point {
		double pos[3];
		double nearestPos[3];
		double distance;

	public:
		point(double pointpos[3], double near[3], double dist);
		double* getPos();
		double* getNearestPos();
		double getDistance();
	};

	int currpos;
	int size;
	vector<point> points;

public:
	pointStore(int size);
	void add(double pointpos[3], double near[3], double dist);
};