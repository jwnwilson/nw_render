#include "LightArea.h"
#include "Matrix4D.h"

LightArea::LightArea(void)
{
	type=AREALIGHT;
	segments = 16;
	width = 2.;
	height = 1.;
	direction = Vector3D(0,-1,0);
	pos = Vector3D(0,2,0);
	points[0] = Vector3D(-(width/2),0,-(height/2));
	points[1] = Vector3D((width/2),0,-(height/2));
	points[2] = Vector3D((width/2),0,(height/2));
	points[3] = Vector3D(-(width/2),0,(height/2));
}

LightArea::~LightArea(void)
{
}
void LightArea::setSegments(int s)
{
	segmentPos.clear();
	Vector3D tempPos;
	segments = s;

	Xdirect = points[1] - points[0];
	Ydirect = points[3] - points[0];

	Xdirect = Xdirect * (float(1)/(sqrt(float(s))));
	Ydirect = Ydirect * (float(1)/(sqrt(float(s))));

	for( int i=0; i< s; i++)
	{
		int segRow = i / sqrt(float(s)), segCol = i % int(sqrt(float(s)));
		Vector3D tempPos = points[0] + (Xdirect * segRow) + (Ydirect * segCol);
		segmentPos.push_back(tempPos);
	}
}

void LightArea::setInterest(const Vector3D& v)
{
	Matrix4D rotation;
	Vector4D Xdirection, Ydirection;
	int segLen = sqrt(float(segments));

	direction = (pos - v).normalize();
	rotation.rotXYZ(90,0,0);
	Ydirection =  rotation * Vector4D(direction);
	Xdirection = Vector4D(direction).cross(Ydirection);
	
	Xdirect = Vector3D(Xdirection.x,Xdirection.y,Xdirection.z);
	Ydirect = Vector3D(Ydirection.x,Ydirection.y,Ydirection.z);

	points[0] = pos - (Ydirect * (height/2)) - (Xdirect * (width/2));
	points[1] = pos - (Ydirect * (height/2)) + (Xdirect * (width/2));
	points[2] = pos + (Ydirect * (height/2)) + (Xdirect * (width/2));
	points[3] = pos + (Ydirect * (height/2)) - (Xdirect * (width/2));

	setSegments(segments);

	//Xdirect = (points[1] - points[0]) * (float(1)/segLen);
	//Ydirect = (points[3] - points[0])* (float(1)/segLen);

	// xdirection = direction * rotate 90 degrees
	// ydirection = xdirection cross direction
	//pointings = xdireciton * width/2 + ydirection * height/2
}
void LightArea::setPosition(const Vector3D& v)
{
	pos = v;
	setInterest(direction);
}