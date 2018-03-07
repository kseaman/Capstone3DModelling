#pragma once
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