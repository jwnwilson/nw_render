#include "ModelSys.h"
#include "MaterialLambert.h"
#include "ImplicitPlane.h"
#include "ImplicitCube.h"
#include "ImplicitSphere.h"
#include "FaceSD.h"
#include "EdgeSD.h"
#include <set>
#include <map>

#define NEXT(i) (((i)+1)%3)
#define PREV(i) (((i)+2)%3)

ModelSys::ModelSys(void)
{
}

ModelSys::~ModelSys(void)
{
}
void ModelSys::FacesToTriangles(Face *f,vector<Face*> &vf)
{

	for(int i = 0;i<(f->vertexPos.size()-2);i++)
	{
		Face *tempf = new Face;
		tempf->vertexPos.push_back(f->vertexPos[0]);
		tempf->vertexPos.push_back(f->vertexPos[i+1]);
		tempf->vertexPos.push_back(f->vertexPos[i+2]);

		tempf->vertexNorm.push_back(f->vertexNorm[0]);
		tempf->vertexNorm.push_back(f->vertexNorm[i+1]);
		tempf->vertexNorm.push_back(f->vertexNorm[i+2]);

		tempf->vertexUV.push_back(f->vertexUV[0]);
		tempf->vertexUV.push_back(f->vertexUV[i+1]);
		tempf->vertexUV.push_back(f->vertexUV[i+2]);

		vf.push_back(tempf);
	}
}
void ModelSys::averageNorms(Model* mod)
{
	vector<Vector4D> newNormals;
	for(int i=0; i< origPos->size();i++)
	{
		newNormals.push_back(Vector4D());
	}
	
	map<Vector3D*,Vector4D*> posNormal;
	int count =0;
	for(int i=0;i<origFaces->size();i++)
	{
		Face *f = (*origFaces)[i];
		for(int j=0;j<3;j++)
		{
			if(posNormal[f->vertexPos[j]]!=NULL)
			{
				Vector4D* v = posNormal[f->vertexPos[j]];
				*v =  *f->vertexNorm[j] + *posNormal[f->vertexPos[j]];
				
			}
			else
			{
				posNormal[f->vertexPos[j]] = &newNormals[count];
				count++;

				Vector4D* v = posNormal[f->vertexPos[j]];
				*v =  *f->vertexNorm[j];			
			}
		}
	}
	vector<int> normalIndex;

	for( map<Vector3D*,Vector4D*>::iterator iter = posNormal.begin(); iter != posNormal.end(); ++iter )
	{
		for(int i = 0; i< newNormals.size();i++)
		{
			if((*iter).second == &newNormals[i])
			{
				normalIndex.push_back(i);
				i = newNormals.size();
			}
		}
	}
	for(int i=0; i< normalIndex.size();i++)
	{
		(*mod->getNormals()).push_back(newNormals[normalIndex[i]].normalize());
	}
	for(int i=0; i< origPos->size();i++)
	{
		(*origVerts)[i].setNorm(&(*mod->getNormals())[i]);
	}
}

bool ModelSys::prepareForSubD(Model* mod)
{
	// trianglulate model
	vector<Face*> tempfaces;
	vector<int> tempInts;
	for(int i=0;i<mod->getFaces()->size();i++)
	{
		FacesToTriangles((*mod->getFaces())[i],tempfaces );
		delete (*mod->getFaces())[i];
		(*mod->getFaces())[i] = NULL;
	}
	mod->getFaces()->clear();

	for(int i=0;i<tempfaces.size();i++)
	{
		(*mod->getFaces()).push_back(tempfaces[i]);
	}

	int start=0,end=0;

	// reorganise index
	for(int i=0;i<mod->getIndex()->size();i++)
	{
		if((*mod->getIndex())[i] == -1)
		{
			end = i;
			for(int a = 0;a<(end - start - 2);a++)
			{
				tempInts.push_back((*mod->getIndex())[start]);
				tempInts.push_back((*mod->getIndex())[start+a+1]);
				tempInts.push_back((*mod->getIndex())[start+a+2]);
				tempInts.push_back(-1);
			}
			start = end+1;
		}
	}
	mod->getIndex()->clear();
	for(int i=0;i<tempInts.size();i++)
	{
		(*mod->getIndex()).push_back(tempInts[i]);
	}

	// create vertices
	for(int i=0;i<mod->getPositions()->size();i++)
	{
		VertexSD v;
		v.worldPos = &(*mod->getPositions())[i];
		mod->getSDVertices()->push_back(v);
		
	}
	//link faces to vertices
	int currentFace=0;
	for(int i=0;i< mod->getFaces()->size();i++)
	{		
		Face *f = (*mod->getFaces())[i];
		for(int a=0;a<3;a++)
		{
			VertexSD *v = &(*mod->getSDVertices())[(*mod->getIndex())[currentFace+a]];
			f->v[a] = v;
			v->startFace = f;
		}
		currentFace+=4;
	}

	// set edges and link faces to their neibours
	set<EdgeSD> edges;

	for(int i =0; i< mod->getFaces()->size();i++)
	{
		Face *f = (*mod->getFaces())[i];
		for(int a=0;a<3;a++)
		{
			int v0=a, v1 = NEXT(a);
			EdgeSD e(f->v[v0],f->v[v1]);
			if(edges.find(e) == edges.end())
			{
				e.f[0] = f;
				e.f0EdgeNum = a;
				edges.insert(e);
			}
			else
			{
				e = *edges.find(e);
				e.f[0]->f[e.f0EdgeNum] = f;
				f->f[a] = e.f[0];
				edges.erase(e);
			}
		}
	}
	// set vertices boundary and regular
	for( int i =0;i< mod->getSDVertices()->size();i++)
	{
		VertexSD *v = &(*mod->getSDVertices())[i];
		Face *f = v->startFace;
		do{
			f= f->nextFace(v);
		}while(f && f != v->startFace);
		v->boundary = (f==NULL);
		int val = v->valence();
		if(!v->boundary &&  val== 6)
		{
			v->regular = true;
		}
		else if(!v->boundary && val == 4)
		{
			v->regular = true;
		}
		else
		{
			v->regular = false;
		}

	}

	return true;


}
bool ModelSys::subDModel(Model* mod)
{
	//allocate new vertices and faces
	int VertsSize = mod->getSDVertices()->size();

	mod->increaseSubD();

	origFaces = mod->getFaces();
	origFaces--;
	origPos = mod->getPositions();
	origPos--;
	origVerts = mod->getSDVertices();
	origVerts--;
	origIndex = mod->getIndex();
	origIndex--;

	for(int i=0; i< VertsSize;i++)
	{
		mod->getSDVertices()->push_back(VertexSD());
		VertexSD *v = &(*mod->getSDVertices())[mod->getSDVertices()->size()-1];
		v->boundary = (*origVerts)[i].boundary;
		v->regular = (*origVerts)[i].regular;
	}

	for(int i=0; i< origFaces->size();i++)
	{
		for(int j=0;j<4;j++)
		{
			Face *f = new FaceSD();
			(*origFaces)[i]->children[j] = f;
			mod->getFaces()->push_back(f);
		}
	}

	// update original vertex normals
	averageNorms(mod);
	//update original vertex positions
	for(int i=0;i< VertsSize;i++)
	{
		VertexSD* v = &(*mod->getSDVertices())[i];
		Vertex_R temp;

		if(!v->boundary)
		{
			VertexSD *origV = &(*origVerts)[i];
			if(v->regular)
			{
				weightRing(origV,1.f/16.f, temp);
				mod->getPositions()->push_back(temp.getWorld());
				mod->getUVs()->push_back(Vector2D(0,0));
				//mod->getNormals()->push_back(temp.getNorm());
				//mod->getUVs()->push_back(temp.getUV());
				//v->setWorld(&(*mod->getPositions())[mod->getPositions()->size()-1]);
			}
			else
			{	
				weightRing(origV,beta(origV->valence()), temp);
				mod->getPositions()->push_back(temp.getWorld());
				mod->getUVs()->push_back(Vector2D(0,0));
				//mod->getNormals()->push_back(temp.getNorm());
				//mod->getUVs()->push_back(temp.getUV());
				//v->setWorld(&(*mod->getPositions())[mod->getPositions()->size()-1]);
			}
		}
		else
		{
			cout<< "Error, cannot sud-divide uncomplete meshes" << endl;
		}
	}


	//update new vertex positions
	map<EdgeSD,VertexSD*> edgeVerts;
	map<int,int> vertPositions;
	vector<int> vertIndices;

	vector<Vector3D> newPos;
	vector<Vector3D> newNorm;
	
	for(int i=0; i< origFaces->size();i++)
	{
		Face* f = (*origFaces)[i];
		for(int j=0;j<3;j++)
		{
			Vector3D pos;
			Vector4D norm;
			//Vector2D uv;
			EdgeSD edge(f->v[j],f->v[NEXT(j)]);
			VertexSD *v = edgeVerts[edge];
			if(!v){
				mod->getSDVertices()->push_back(VertexSD());
				v = &(*mod->getSDVertices())[mod->getSDVertices()->size()-1];
				v->regular = true;
				v->boundary = (f->f[j] == NULL);
				// start face for all new vertices is the middle face
				v->startFace = f->children[3];

				if(v->boundary)
				{
					pos =  edge.v[0]->getWorld() * 0.5f ;
					norm = edge.v[0]->getNorm() * 0.5f;
					//uv = edge.v[0]->getUV() * 0.5f;
					pos = pos + ( edge.v[1]->getWorld() * 0.5f );
					norm = norm + ( edge.v[1]->getNorm() * 0.5f );
					//uv = uv + ( edge.v[1]->getUV() * 0.5f );
				}
				else
				{
					pos =  edge.v[0]->getWorld() * 3.0f/8.f;
					pos = pos + (edge.v[1]->getWorld()* 3.0f/8.f );
					pos = pos + (f->otherVert(edge.v[0],edge.v[1])->getWorld() * 1.0f/8.f );
					pos = pos + (f->f[j]->otherVert(edge.v[0],edge.v[1])->getWorld() * 1.0f/8.f);

					norm =  edge.v[0]->getNorm() * 3.0f/8.f;
					norm = norm + (edge.v[1]->getNorm()* 3.0f/8.f );
					norm = norm + (f->otherVert(edge.v[0],edge.v[1])->getNorm() * 1.0f/8.f );
					norm = norm + (f->f[j]->otherVert(edge.v[0],edge.v[1])->getNorm() * 1.0f/8.f);

					//uv =  edge.v[0]->getUV() * 3.0f/8.f;
					//uv = uv + (edge.v[1]->getUV()* 3.0f/8.f );
					//uv = uv + (f->otherVert(edge.v[0],edge.v[1])->getUV() * 3.0f/8.f );
					//uv = uv + (f->f[j]->otherVert(edge.v[0],edge.v[1])->getUV() * 3.0f/8.f);
				}
				newPos.push_back(pos);
				newNorm.push_back(norm.normalize());
				//mod->getUVs()->push_back(uv);
				vertPositions[mod->getSDVertices()->size()-1] = (newPos.size()-1+mod->getPositions()->size());
				//v->setWorld(&(*mod->getPositions())[mod->getPositions()->size()-1]);
			}
			edgeVerts[edge] = v;
			vertIndices.push_back(mod->getSDVertices()->size()-1);
		}
	}
	// add new positions and normals
	for(int i=0;i< newPos.size();i++)
	{
		mod->getPositions()->push_back(newPos[i]);
		mod->getNormals()->push_back(newNorm[i]);
		mod->getUVs()->push_back(Vector2D(0,0));
	}

	// link vertices to normals and positions
	for( map<int,int>::iterator iter = vertPositions.begin(); iter != vertPositions.end(); ++iter )
	{
		VertexSD* v = &(*mod->getSDVertices())[(*iter).first];
		v->setWorld(&(*mod->getPositions())[(*iter).second]);
		v->setNorm(&(*mod->getNormals())[(*iter).second]);
		v->setUV(&(*mod->getUVs())[(*iter).second]);
	}
	int i=0;
	for( map<EdgeSD,VertexSD*>::iterator iter = edgeVerts.begin(); iter != edgeVerts.end(); ++iter )
	{
		edgeVerts[(*iter).first] = &(*mod->getSDVertices())[vertIndices[i]];
		i++;
	}

	for(int i=0; i< VertsSize;i++)
	{
		VertexSD *v = &(*mod->getSDVertices())[i];
		v->setWorld(&(*mod->getPositions())[i]);
		v->setNorm(&(*mod->getNormals())[i]);
		v->setUV(&(*mod->getUVs())[i]);
		(*origVerts)[i].child = v;
	}
	// update face objects
		// update existing vertices face pointers
	for(int i=0;i<VertsSize;i++)
	{
		VertexSD *v = &(*origVerts)[i];
		int vertNum = v->startFace->vnum(v);
		v->child->startFace = v->startFace->children[vertNum];
	}
		// update face niebours
	for(int i=0;i<origFaces->size();i++)
	{
		Face *f = (*origFaces)[i];
		for(int j=0;j<3;j++)
		{
			f->children[3]->f[j] = f->children[NEXT(j)];
			f->children[j]->f[NEXT(j)] = f->children[3];

			Face* f2 = f->f[j];
			if( f2 != NULL)
				f->children[j]->f[j] = f2->children[f2->vnum(f->v[j])];
			f2 = f->f[PREV(j)];
			if( f2!=NULL)
				f->children[j]->f[PREV(j)] = f2->children[f->vnum(f->v[j])];
		}
	}
		// update face vertex pointers
	for(int i=0;i<origFaces->size();i++)
	{
		Face *f = (*origFaces)[i];
		for(int j=0;j<3;j++)
		{
			f->children[j]->v[j] = f->v[j]->child;
			VertexSD *v = edgeVerts[EdgeSD(f->v[j],f->v[NEXT(j)])];
			f->children[j]->v[NEXT(j)] = v;
			f->children[NEXT(j)]->v[j] = v;
			f->children[3]->v[j] = v;
		}
	}
	//need a method for finding positions, normals and UVs from v
	// compare position pointers to poisition address in array and use that instead of v
	//for(int i=0; i< mod->getFaces()->size() ; i++)
	//{
	//	Face *f = (*mod->getFaces())[i];
	//	for(int j=0; j< 3;j++)
	//	{
	//		VertexSD v1 = *f->v[j];
	//		f->vertexPos.push_back(&v1.getWorld());
	//		f->vertexNorm.push_back(&v1.getNorm());
	//		//f->vertexUV.push_back(&f->v[j]->getUV());
	//	}
	//}

	return true;
}
float ModelSys::beta(int val)
{
	if(val == 3) 
		return 3.f/16.f;
	else
		return 3.f/(8.f*val);
}
vector<VertexSD*> ModelSys::getVerts(VertexSD* v)
{
	vector<VertexSD*> vv;
	Face *f = v->startFace, *startFace = v->startFace ;
	if(!v->boundary)
	{
		do
		{
			vv.push_back((f->nextVert(v)));
			f = (f->nextFace(v));
		}while(f!= startFace);
	}
	else
	{
		Face* f2 = f, *f3;
		while((f3 = f2->nextFace(v)) !=NULL)
			f2 = f3;
		vv.push_back(f->nextVert(v));
		do
		{
			vv.push_back(f2->prevVert(v));
			f2 = f2->prevFace(v);
		}while(f2!=NULL);
	}
	return vv;
}
void ModelSys::weightRing(VertexSD* v, float beta,Vertex_R &vert)
{
	vector<VertexSD*> verts;
	verts= getVerts(v);
	int valence = v->valence();
	vert.setWorld( v->getWorld()*( 1- valence* beta));
	//vert.setNorm( v->getNorm()*( 1- valence* beta));
	//vert.setUV( v->getUV()*( 1- valence* beta));
	for(int i =0; i< valence; i++)
	{
		vert.setWorld( vert.getWorld() + (verts[i]->getWorld()*beta));
		//vert.setNorm( vert.getNorm() + (verts[i]->getWorld()*beta));
		//vert.setUV( vert.getUV() + (verts[i]->getUV()*beta));
	}
}
bool ModelSys::LoopSubD(Model* mod, int subD)
{
	// either copy model and replace faces with faceSDs
	// simply overwrite faces with facesSDs and overwrite model - this is more efficient and no need for a copy
	prepareForSubD(mod);
	for(int i=0;i<subD;i++)
	{
		subDModel(mod);
	}
	return true;
}

void ModelSys::createPlane(float wid,float hei,Vector3D pos,Model* mod)
{
	mod->parameters.position = pos;
	mod->parameters.sizeX = wid;
	mod->parameters.sizeY = hei;

	if(mod->getType() == MODBASE)
	{
		/*Vertex_R v1;
		v1.setWorld(Vector3D(pos.x-wid,pos.y-hei,pos.z));
		v1.setNorm(Vector4D(0,0,-1,1));
		v1.setUV(Vector2D(0,0));
		mod.vertices.push_back(v1);
		v1.setWorld(Vector3D(pos.x+wid,pos.y-hei,pos.z));
		v1.setNorm(Vector4D(0,0,-1,1));
		v1.setUV(Vector2D(1,0));
		mod.vertices.push_back(v1);	
		v1.setWorld(Vector3D(pos.x+wid,pos.y+hei,pos.z));
		v1.setNorm(Vector4D(0,0,-1,1));
		v1.setUV(Vector2D(1,1));
		mod.vertices.push_back(v1);
		v1.setWorld(Vector3D(pos.x-wid,pos.y+hei,pos.z));
		v1.setNorm(Vector4D(0,0,-1,1));
		v1.setUV(Vector2D(0,1));
		mod.vertices.push_back(v1);

		mod.index.push_back(0);
		mod.index.push_back(1);
		mod.index.push_back(2);
		mod.index.push_back(3);
		mod.index.push_back(-1);*/
	}
	else
	{
		vector<Vector3D> *vpos = mod->getPositions();
		vector<Vector4D> *norm = mod->getNormals();
		vector<Vector2D> *uv = mod->getUVs();

		vpos->push_back(Vector3D(pos.x-wid,pos.y-hei,pos.z));
		norm->push_back(Vector4D(0,0,-1,1));
		uv->push_back(Vector2D(0,0));

		vpos->push_back(Vector3D(pos.x+wid,pos.y-hei,pos.z));
		norm->push_back(Vector4D(0,0,-1,1));
		uv->push_back(Vector2D(1,0));

		vpos->push_back(Vector3D(pos.x+wid,pos.y+hei,pos.z));
		norm->push_back(Vector4D(0,0,-1,1));
		uv->push_back(Vector2D(1,1));

		vpos->push_back(Vector3D(pos.x-wid,pos.y+hei,pos.z));
		norm->push_back(Vector4D(0,0,-1,1));
		uv->push_back(Vector2D(0,1));

		Face *f = new Face;
		f->vertexPos.push_back(&(*vpos)[0]);
		f->vertexPos.push_back(&(*vpos)[1]);
		f->vertexPos.push_back(&(*vpos)[2]);
		f->vertexPos.push_back(&(*vpos)[3]);
		f->vertexNorm.push_back(&(*norm)[0]);
		f->vertexNorm.push_back(&(*norm)[1]);
		f->vertexNorm.push_back(&(*norm)[2]);
		f->vertexNorm.push_back(&(*norm)[3]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
	}

	//mod->material= new MaterialLambert();

	mod->boundingShape=new ImplicitPlane();
	mod->boundingShape->setPoints(mod);

}
void ModelSys::createSphere(float rad,Vector3D pos,Model* mod)
{
	mod->parameters.position = pos;
	mod->parameters.radius = rad;
	mod->boundingShape = new ImplicitSphere();
	mod->boundingShape->setPoints(mod);
}
void ModelSys::createCube(float size, Vector3D pos,Model* mod)
{
	mod->parameters.position = pos;
	mod->parameters.sizeX = size;
	mod->parameters.sizeY = size;
	mod->parameters.sizeZ = size;

	if(mod->getType() == MODBASE)
	{
		//ModelBase plane[6];
		//for(int i=0;i<6;i++)
		//{
		//	createPlane(size,size,Vector3D(0,0,-size),plane[i]);
		//}
		//rotate(&plane[1],Vector3D(90,0,0));	
		//rotate(&plane[2],Vector3D(-90,0,0));
		//rotate(&plane[3],Vector3D(0,90,0));
		//rotate(&plane[4],Vector3D(0,-90,0));
		//rotate(&plane[5],Vector3D(180,0,0));
		//
		//for(int i=0;i<6;i++)
		//{
		//	translate(&plane[i],pos);
		//}

		//vector<Model*> planesVec;
		//for(int i=0;i<6;i++)
		//{
		//	planesVec.push_back(&plane[i]);
		//}
		////mesh.boundingShape->model=&mesh;

		//mergeModels(&mesh,&plane[0]);
		//mergeModels(&mesh,&plane[1]);
		//mergeModels(&mesh,&plane[2]);
		//mergeModels(&mesh,&plane[3]);
		//mergeModels(&mesh,&plane[4]);
		//mergeModels(&mesh,&plane[5]);
	}
	else
	{
		vector<Vector3D> *vpos = mod->getPositions();
		vector<Vector4D> *norm = mod->getNormals();
		vector<Vector2D> *uv = mod->getUVs();

		vpos->push_back(Vector3D(-1,-1,1));
		vpos->push_back(Vector3D(1,-1,1));
		vpos->push_back(Vector3D(1,1,1));
		vpos->push_back(Vector3D(-1,1,1));
		vpos->push_back(Vector3D(-1,-1,-1));
		vpos->push_back(Vector3D(1,-1,-1));
		vpos->push_back(Vector3D(1,1,-1));
		vpos->push_back(Vector3D(-1,1,-1));

		norm->push_back(Vector4D(0,0,-1,1));
		norm->push_back(Vector4D(0,0,1,1));
		norm->push_back(Vector4D(0,-1,0,1));
		norm->push_back(Vector4D(0,1,0,1));
		norm->push_back(Vector4D(-1,0,0,1));
		norm->push_back(Vector4D(1,0,0,1));

		uv->push_back(Vector2D(0,0));
		uv->push_back(Vector2D(0,1));
		uv->push_back(Vector2D(1,1));
		uv->push_back(Vector2D(1,0));

		Face *f = new Face;
		f->vertexPos.push_back(&(*vpos)[4]);
		f->vertexPos.push_back(&(*vpos)[5]);
		f->vertexPos.push_back(&(*vpos)[6]);
		f->vertexPos.push_back(&(*vpos)[7]);
		f->vertexNorm.push_back(&(*norm)[0]);
		f->vertexNorm.push_back(&(*norm)[0]);
		f->vertexNorm.push_back(&(*norm)[0]);
		f->vertexNorm.push_back(&(*norm)[0]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		f = new Face;
		f->vertexPos.push_back(&(*vpos)[1]);
		f->vertexPos.push_back(&(*vpos)[0]);
		f->vertexPos.push_back(&(*vpos)[3]);
		f->vertexPos.push_back(&(*vpos)[2]);
		f->vertexNorm.push_back(&(*norm)[1]);
		f->vertexNorm.push_back(&(*norm)[1]);
		f->vertexNorm.push_back(&(*norm)[1]);
		f->vertexNorm.push_back(&(*norm)[1]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		f = new Face;
		f->vertexPos.push_back(&(*vpos)[5]);
		f->vertexPos.push_back(&(*vpos)[4]);
		f->vertexPos.push_back(&(*vpos)[0]);
		f->vertexPos.push_back(&(*vpos)[1]);
		f->vertexNorm.push_back(&(*norm)[2]);
		f->vertexNorm.push_back(&(*norm)[2]);
		f->vertexNorm.push_back(&(*norm)[2]);
		f->vertexNorm.push_back(&(*norm)[2]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		f = new Face;
		f->vertexPos.push_back(&(*vpos)[2]);
		f->vertexPos.push_back(&(*vpos)[3]);
		f->vertexPos.push_back(&(*vpos)[6]);
		f->vertexPos.push_back(&(*vpos)[7]);
		f->vertexNorm.push_back(&(*norm)[3]);
		f->vertexNorm.push_back(&(*norm)[3]);
		f->vertexNorm.push_back(&(*norm)[3]);
		f->vertexNorm.push_back(&(*norm)[3]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		f = new Face;
		f->vertexPos.push_back(&(*vpos)[0]);
		f->vertexPos.push_back(&(*vpos)[4]);
		f->vertexPos.push_back(&(*vpos)[7]);
		f->vertexPos.push_back(&(*vpos)[3]);
		f->vertexNorm.push_back(&(*norm)[4]);
		f->vertexNorm.push_back(&(*norm)[4]);
		f->vertexNorm.push_back(&(*norm)[4]);
		f->vertexNorm.push_back(&(*norm)[4]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		f = new Face;
		f->vertexPos.push_back(&(*vpos)[5]);
		f->vertexPos.push_back(&(*vpos)[1]);
		f->vertexPos.push_back(&(*vpos)[2]);
		f->vertexPos.push_back(&(*vpos)[6]);
		f->vertexNorm.push_back(&(*norm)[5]);
		f->vertexNorm.push_back(&(*norm)[5]);
		f->vertexNorm.push_back(&(*norm)[5]);
		f->vertexNorm.push_back(&(*norm)[5]);
		f->vertexUV.push_back(&(*uv)[0]);
		f->vertexUV.push_back(&(*uv)[1]);
		f->vertexUV.push_back(&(*uv)[2]);
		f->vertexUV.push_back(&(*uv)[3]);
		mod->getFaces()->push_back(f);
		//f = new Face;
	}

	//mod->boundingShape=new ImplicitCube();
	//mod->boundingShape->setPoints(mod);
}
void ModelSys::mergeModels(Model* mod1,Model* mod2)
{
	if(mod1->getType() == MODBASE && mod2->getType() == MODBASE )
	{
		int size= mod1->getVertices()->size();
		for(int i=0;i<mod2->getVertices()->size();i++)
		{
			mod1->getVertices()->push_back((*mod2->getVertices())[i]);
		}
		for(int i=0;i<mod2->getIndex()->size();i++)
		{
			if((*mod2->getIndex())[i]>=0)
			{
				mod1->getIndex()->push_back((*mod2->getIndex())[i]+size);
			}
			else
			{
				mod1->getIndex()->push_back((*mod2->getIndex())[i]);
			}
		}
	}

}
void ModelSys::translate(Model* mod,Vector3D trans)
{
	mod->parameters.position = mod->parameters.position + trans;

	if(mod->getType() == MODBASE)
	{
		for(int i=0;i<mod->getVertices()->size();i++)
		{
			Vertex_R *v=&(*mod->getVertices())[i];
			v->setWorld(v->getWorld()+trans);
		}
		if(mod->boundingShape!=NULL)
		{
			mod->boundingShape->setPoints(mod);
		}
	}
	else
	{
		for(int i=0;i<mod->getPositions()->size();i++)
		{
			(*mod->getPositions())[i]= (*mod->getPositions())[i]+trans;
		}
		if(mod->boundingShape!=NULL)
		{
			mod->boundingShape->setPoints(mod);
		}
	}
	/*Matrix4D mat;
	mat.trans(trans.x,trans.y,trans.z);
	mod->worldTrans=mod->worldTrans*mat;*/
}
void ModelSys::rotate(Model* mod,Vector3D rot)
{
	mod->parameters.rotation = mod->parameters.rotation + rot;
	Matrix4D mat;
	mat.rotXYZ(rot.x,rot.y,rot.z);
	Vector3D toOrig = Vector3D(0,0,0) - mod->parameters.position;

	if(mod->getType() == MODBASE)
	{
	/*	for(int i=0;i<mod->vertices.size();i++)
		{
			v->setWorld(v->getWorld()-toOrig);
			v->setWorld(mat*Vector4D(v->getWorld()));
			v->setWorld(v->getWorld()+toOrig);
			v->setNorm(mat*v->getNorm());
		}
		if(mod->boundingShape!=NULL)
		{
			mod->boundingShape->setPoints(mod);
		}*/
	}
	else
	{
		for(int i=0;i<mod->getPositions()->size();i++)
		{
			(*mod->getPositions())[i]= (*mod->getPositions())[i]-toOrig;
			(*mod->getPositions())[i]= mat*(*mod->getPositions())[i];
			(*mod->getPositions())[i]= (*mod->getPositions())[i]+toOrig;
		}
		for(int i=0;i<mod->getNormals()->size();i++)
		{
			(*mod->getNormals())[i]= mat*(*mod->getNormals())[i];
		}
		if(mod->boundingShape!=NULL)
		{
			mod->boundingShape->setPoints(mod);
		}
	}
}
void ModelSys::scale(Model* mod,Vector3D sca)
{
	mod->parameters.scale = mod->parameters.scale * sca;

	Matrix4D mat;
	mat.scale(sca.x,sca.y,sca.z);
	Vector3D toOrig = Vector3D(0,0,0) - mod->parameters.position;
	if(mod->getType() == MODBASE)
	{
		/*for(int i=0;i<mod->vertices.size();i++)
		{
			Vertex_R *v=&mod->vertices[i];
			Vector3D toOrig;
			toOrig=mod->worldTrans*Vector4D(0,0,0,1);
			v->setWorld(v->getWorld()-toOrig);
			v->setWorld(mat*Vector4D(v->getWorld()));
			v->setWorld(v->getWorld()+toOrig);
		}*/
	}
	else
	{
		for(int i=0;i<mod->getPositions()->size();i++)
		{
			(*mod->getPositions())[i]= (*mod->getPositions())[i]-toOrig;
			(*mod->getPositions())[i]= mat*(*mod->getPositions())[i];
			(*mod->getPositions())[i]= (*mod->getPositions())[i]+toOrig;
		}
	}
	if(mod->boundingShape!=NULL)
	{
		mod->boundingShape->setPoints(mod);
	}
}