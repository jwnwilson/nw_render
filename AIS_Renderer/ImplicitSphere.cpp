#include "ImplicitSphere.h"
#include "Model.h"
#include <limits>

ImplicitSphere::ImplicitSphere(void)
{
	radius = 1;
	origin = Vector3D(0,0,0);
}

ImplicitSphere::~ImplicitSphere(void)
{
}

void ImplicitSphere::setPoints(Model* mod)
{
	radius = mod->parameters.radius;
	origin = mod->parameters.position;

}
bool ImplicitSphere::implicitShapeCheck(Ray* r,const Model* m)
{
	float A,B,C,t0,t1,quad1,discrim ,uy,uz,theta,phi, u,v,t;
	Vector3D posOrigin = r->position - origin;
	A= (r->getDirection().x*r->getDirection().x)+ (r->getDirection().y*r->getDirection().y)+(r->getDirection().z*r->getDirection().z);
	B= 2*( (r->getDirection().x*posOrigin.x) + (r->getDirection().y*posOrigin.y) + (r->getDirection().z*posOrigin.z) ); 
	C= (posOrigin.x*posOrigin.x) + (posOrigin.y*posOrigin.y) + (posOrigin.z*posOrigin.z) - (radius * radius);

	quad1 = (B*B)-(4.*A*C);

	if( quad1< 0)
		return false;
	discrim = sqrt(quad1);

	t0 = (-B - discrim )/ (2.*A);
	t1 = (-B + discrim )/ (2.*A);

	if( t0 < t1 && t0 > 0)
		t= t0;
	else
		t = t1;

	if(t < 0.001)
		return false;

	return true;
}
bool ImplicitSphere::getRayImplicitShapeIntersection(Ray* r,float &t,const Model* m)
{
	float A,B,C,t0,t1,quad1,discrim ,uy,uz,theta,phi, u,v;
	Vector3D posOrigin = r->position - origin;
	A= (r->getDirection().x*r->getDirection().x)+ (r->getDirection().y*r->getDirection().y)+(r->getDirection().z*r->getDirection().z);
	B= 2*( (r->getDirection().x*posOrigin.x) + (r->getDirection().y*posOrigin.y) + (r->getDirection().z*posOrigin.z) ); 
	C= (posOrigin.x*posOrigin.x) + (posOrigin.y*posOrigin.y) + (posOrigin.z*posOrigin.z) - (radius * radius);

	quad1 = (B*B)-(4.*A*C);

	if( quad1< 0)
		return false;
	discrim = sqrt(quad1);

	t0 = (-B - discrim )/ (2.*A);
	t1 = (-B + discrim )/ (2.*A);

	if( t0 < t1)
		t= t0;
	else 
		t = t1;

	if(t < 0.001)
		return false;

	if(t< r->minT)
	{
		r->minT = t;
		if(r->pointHit!=NULL)
		{
			delete r->pointHit;
		}
		r->pointHit= new Vertex_R;
		r->pointHit->setWorld(r->position+(r->getDirection()*(t)));
		r->pointHit->setNorm((r->pointHit->getWorld() - origin ).normalize());


		Vector3D vn, ve, vp;
		vp = (r->pointHit->getWorld() - origin).normalize();
		vn= Vector3D(0,1,0);
		ve= Vector3D(1,0,0);
		
		float phi = acos( -vn.dot(vp));

		v = phi / PI;

		theta = ( acos(vp.dot(ve)) / sin(phi) ) / ( 2 * PI);

		if ( vp.dot( vn.cross(ve) ) > 0 )
			  u = theta; 
		else
			  u = 1 - theta; 

		r->pointHit->setUV(Vector2D(u,v));

		//ux = r->pointHit->getWorld().x - origin.x;
		/*uy = r->pointHit->getWorld().y;
		uz = r->pointHit->getWorld().z;

		theta = acos( (uz / radius));
		phi = asin( (uy /(radius* sin(theta))));

		u = phi / (2* PI);
		v = theta / PI;

		u=(u+1)/2;
		v=(v+1)/2;*/

		
	}

	return true;
}