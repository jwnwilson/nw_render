#pragma once

// a convient way to store ray object intersections

class Intersection
{
public:
	Intersection(void);
	~Intersection(void);
	int modelNo,indexNo[3],face;

};
