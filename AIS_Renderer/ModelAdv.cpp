#include "ModelAdv.h"

ModelAdv::ModelAdv(void)
{
	type = MODADV;
	vector<Vector3D> v;
	vector<Face*> f;
	vector<int> i;
	vector<VertexSD> ve;	
	vector<Vector4D> n;
	vector<Vector2D> u;
	vector<EdgeSD> ed;

	positions.push_back(v);
	normals.push_back(n);
	UVs.push_back(u);
	faces.push_back(f);
	Index.push_back(i);
	Vertices.push_back(ve);
	subDEdges.push_back(ed);
	parentModel = NULL;
	childModel = NULL;
}

ModelAdv::~ModelAdv(void)
{
	for(int i=0; i< faces.size();i++)
	{
		for(int j=0; j< faces[i].size();j++)
		{
			if(faces[i][j] !=NULL)
				delete faces[i][j];
		}
	}
}

void ModelAdv::operator=(ModelAdv& m)
{
	Model::operator=(m);
	positions = m.positions;
	normals = m.normals;
	UVs = m.UVs;
	faces = m.faces;
	Index = m.Index;
	Vertices = m.Vertices;
	subDEdges = m.subDEdges;;
}

bool ModelAdv::rayAgaintModel(Ray* r,float &t)
{
	if(implicit==true)
	{
		if(boundingShape->getRayImplicitShapeIntersection(r,t,this)==true)
		{
			//r->pointHit->setNorm(r->pointHit->getNorm().normalize());
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(rayIntersectInModel(r,t))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool ModelAdv::rayIntersectInModel(Ray* ray1,float &t)const
{
	bool hit= false;
	if(boundingShape != NULL)
	{
		if(boundingShape->implicitShapeCheck(ray1,this)== false)
			return false;
	}
	if(subD ==0)
	{
		for(int i=0;i< faces[subD].size();i++)
		{
			for(int a=0;a< float(faces[subD][i]->vertexPos.size())/3.0;a++)
			{
				Intersection inter;
				inter.indexNo[0]=0;
				inter.indexNo[1]=a+1;
				inter.indexNo[2]=a+2;
				inter.face = i;

				if(getRayIntersecPoint(ray1,&inter,t))
						hit = true;
			}
		}
	}
	else
	{
		for(int i=0;i< faces.size();i++)
		{
			for(int a=0;a< 3;a++)
			{
				Intersection inter;
				inter.indexNo[0]=0;
				inter.indexNo[1]=1;
				inter.indexNo[2]=2;
				inter.face = i;

				if(getRayIntersecPoint2(ray1,&inter,t))
						hit = true;
			}
		}
	}
	if(hit == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ModelAdv::increaseSubD()
{
	subD++;
	if(faces.size()<(subD+1))
	{
		vector<Face*> f;
		faces.push_back(f);

		vector<Vector3D> v;
		positions.push_back(v);

		vector<Vector4D> n;
		normals.push_back(n);

		vector<Vector2D> u;
		UVs.push_back(u);

		vector<int> i;
		Index.push_back(i);

		vector<VertexSD> ve;
		Vertices.push_back(ve);

		vector<EdgeSD> ed;
		subDEdges.push_back(ed);
	}
	
}
void ModelAdv::decreaseSubD()
{
	if(subD != 0)
	{
		subD--;
	}
}
bool ModelAdv::getRayIntersecPoint(Ray* ray1,const Intersection* inter,float &t)const
{
	//const Vertex_R* v[3];
	float b3;
	Vector3D const *v[3];
	Vector4D const*n[3];
	Vector2D const *uvs[3];
	for(int i=0;i<3;i++)
	{
		v[i]= faces[subD][inter->face]->vertexPos[inter->indexNo[i]];
		n[i]= faces[subD][inter->face]->vertexNorm[inter->indexNo[i]];
		uvs[i]= faces[subD][inter->face]->vertexUV[inter->indexNo[i]];
	}
	Vector3D tb1b2,s1,s2,e1,e2,s,normal;
	e1=*v[1]-*v[0];
	e2=*v[2]-*v[0];
	s= ray1->position-*v[0];
	s1=ray1->getDirection().cross(e2);
	s2=s.cross(e1);
	tb1b2=Vector3D(s2.dot(e2),s1.dot(s),s2.dot(ray1->getDirection()))*((1/(s1.dot(e1))));
	b3=(1-tb1b2.y-tb1b2.z);
	if(smooth == true)
	{
		normal = (*n[0] * b3) + (*n[1] * tb1b2.y) + (*n[2] * tb1b2.z);
	}
	else
	{
		normal=(e2.cross(e1)).modulate();
		normal.x = -normal.x;
		normal.y = -normal.y;
		normal.z = -normal.z;
	}

	if(tb1b2.x>0)
	{
		if(tb1b2.y>=0&&tb1b2.y<=1&&tb1b2.z>=0&&tb1b2.z<=1&&b3>=0&&b3<=1)
		{	
			if(tb1b2.x< ray1->minT)
			{
				if(ray1->pointHit!=NULL)
				{
					delete ray1->pointHit;
					ray1->pointHit=NULL;
				}
				ray1->pointHit= new Vertex_R;
				ray1->pointHit->setWorld(ray1->getRayPoint(tb1b2.x));
				ray1->pointHit->setNorm(normal);
				Vector2D uv = ((*uvs[0] * b3) + (*uvs[1] * tb1b2.y) + (*uvs[2] * tb1b2.z));
				ray1->pointHit->setUV(uv);
				ray1->minT = tb1b2.x;
			}
			//t=tb1b2.x;
			
			return true;
		}
	}
	return false;
}
bool ModelAdv::getRayIntersecPoint2(Ray* ray1,const Intersection* inter,float &t)const
{
	//const Vertex_R* v[3];
	float b3;
	VertexSD const *v[3];
	for(int i=0;i<3;i++)
	{
		v[i]= faces[subD][inter->face]->v[i];
	}
	Vector3D tb1b2,s1,s2,e1,e2,s,normal;
	e1=v[1]->getWorld()-v[0]->getWorld();
	e2=v[2]->getWorld()-v[0]->getWorld();
	s= ray1->position-v[0]->getWorld();
	s1=ray1->getDirection().cross(e2);
	s2=s.cross(e1);
	tb1b2=Vector3D(s2.dot(e2),s1.dot(s),s2.dot(ray1->getDirection()))*((1/(s1.dot(e1))));
	b3=(1-tb1b2.y-tb1b2.z);
	if(smooth == true)
	{
		normal = (v[0]->getNorm() * b3) + (v[1]->getNorm() * tb1b2.y) + (v[2]->getNorm() * tb1b2.z);
	}
	else
	{
		normal=(e2.cross(e1)).modulate();
		normal.x = -normal.x;
		normal.y = -normal.y;
		normal.z = -normal.z;
	}

	if(tb1b2.x>0)
	{
		if(tb1b2.y>=0&&tb1b2.y<=1&&tb1b2.z>=0&&tb1b2.z<=1&&b3>=0&&b3<=1)
		{	
			if(tb1b2.x< ray1->minT)
			{
				if(ray1->pointHit!=NULL)
				{
					delete ray1->pointHit;
					ray1->pointHit=NULL;
				}
				ray1->pointHit= new Vertex_R;
				ray1->pointHit->setWorld(ray1->getRayPoint(tb1b2.x));
				ray1->pointHit->setNorm(normal);
				//Vector2D uv = ((*uvs[0] * b3) + (*uvs[1] * tb1b2.y) + (*uvs[2] * tb1b2.z));
				Vector2D uv(0,0);
				ray1->pointHit->setUV(uv);
				ray1->minT = tb1b2.x;
			}
			//t=tb1b2.x;
			
			return true;
		}
	}
	return false;
}