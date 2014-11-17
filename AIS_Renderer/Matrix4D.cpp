#include "Matrix4D.h"
#include "Vertex_R.h"
#include <iomanip>

Matrix4D::Matrix4D(void)
{
	for(int col=0; col<4; col++)
	{
		for(int row=0;row<4; row++)
		{
			matrix[row][col]= 0;
		}
	}
}

Matrix4D::Matrix4D(float mat[4][4])
{
	for(int col=0; col<4; col++)
	{
		for(int row=0;row<4; row++)
		{
			matrix[row][col]= mat[row][col];
		}
	}
}
void Matrix4D::emptyMatrix()
{
	for(int col=0; col<4; col++)
	{
		for(int row=0;row<4; row++)
		{
			matrix[row][col]= 0;
		}
	}
}
float Matrix4D::getMatrix(int a, int b)const
{
	return matrix[a][b];
}

Vector4D Matrix4D:: operator * (const Vector4D& vec)const
{
	float x, y, z, h;
	x = (vec.x* matrix[0][0] + vec.y*matrix[0][1] + vec.z*matrix[0][2] + vec.h*matrix[0][3]);
	y = (vec.x* matrix[1][0] + vec.y*matrix[1][1] + vec.z*matrix[1][2] + vec.h*matrix[1][3]);
	z = (vec.x* matrix[2][0] + vec.y*matrix[2][1] + vec.z*matrix[2][2] + vec.h*matrix[2][3]);
	h = (vec.x* matrix[3][0] + vec.y*matrix[3][1] + vec.z*matrix[3][2] + vec.h*matrix[3][3]);

	Vector4D vec2(x,y,z,h);
	return vec2;
	
}

Matrix4D Matrix4D:: operator * (const Matrix4D& y)const
{
	Matrix4D z;

	for(int col=0; col<4; col++)
	{
		for(int row=0; row<4;row++)
		{
			z.matrix[col][row] = matrix[col][0]* y.matrix[0][row] + matrix[col][1]*y.matrix[1][row] +matrix[col][2]*y.matrix[2][row] +matrix[col][3]*y.matrix[3][row];
		}
	}

	return z; 
}
/*
RVertex Matrix4D::operator *(const RVertex& vert)const
{
	float x, y, z, h;
	x = (vert.getX()* getMatrix(0,0) + vert.getY()*getMatrix(0,1) + vert.getZ()*getMatrix(0,2) + vert.getH()*getMatrix(0,3));
	y = (vert.getX()* getMatrix(1,0) + vert.getY()*getMatrix(1,1) + vert.getZ()*getMatrix(1,2) + vert.getH()*getMatrix(1,3));
	z = (vert.getX()* getMatrix(2,0) + vert.getY()*getMatrix(2,1) + vert.getZ()*getMatrix(2,2) + vert.getH()*getMatrix(2,3));
	h = (vert.getX()* getMatrix(3,0) + vert.getY()*getMatrix(3,1) + vert.getZ()*getMatrix(3,2) + vert.getH()*getMatrix(3,3));

	RVertex ver=vert;
	ver.setXYZH(x,y,z,h);
	return ver;
}*/

void Matrix4D::ShowMat()const
{
	for(int row=0;row<4;row++)
	{
		cout<< "{";
		for(int col=0;col<3;col++)
		{
			cout<<setprecision(3)<< fixed << matrix[row][col] << ", ";
		}
		for(int col=3;col<4;col++)
		{
			cout<<setprecision(3)<< fixed << matrix[row][col];
		}
		cout<<"}"<<endl;
	}
}
void Matrix4D::rotXYZ(float degx,float degy,float degz)
{
	Matrix4D matX,matY,matZ;
	matX.rotX(degx);
	matY.rotY(degy);
	matZ.rotZ(degz);
	matX=matX*matY*matZ;
	*this=matX;
}
void Matrix4D::rotX(float deg)
{
	float ang= ((deg/180)*PI);

	float mat1[4][4]= 
	{{1, 0,0,0},
	{0,cos(ang),-sin(ang),0},
	{0,sin(ang),cos(ang),0},
	{0,0,0,1}};

	Matrix4D mat2(mat1);
	*this=mat2;
}

void Matrix4D::rotY(float deg)
{
	float ang= ((deg/180)*PI);

	float mat1[4][4]= 
	{{cos(ang), 0,sin(ang),0},
	{0,1,0,0},
	{-sin(ang),0,cos(ang),0},
	{0,0,0,1}};

	Matrix4D mat2(mat1);

	*this=mat2;
}

void Matrix4D::rotZ(float deg)
{
	float ang= ((deg/180)*PI);

	float mat1[4][4]= 
	{{cos(ang), -sin(ang),0,0},
	{sin(ang),cos(ang),0,0},
	{0,0,1,0},
	{0,0,0,1}};

	Matrix4D mat2(mat1);

	*this=mat2;
}

Matrix4D Matrix4D::veiwTrans(const Vector3D& cam, const Vector3D& intr, const Vector3D& p)const
{
	Vector3D cam1 = intr-cam;
	Vector4D cam2(cam),up(p);
	//float phi, the, d,a;
	//a = cam1.getX()*cam1.getX()+cam1.getY()*cam1.getY();
	//a= sqrt(a);

	//the= acos(cam1.getZ()/a);
	//phi= atan(cam1.getY()/a);
	//d= (cam1.getY()/sin(phi));

	Vector4D w(-cam1.x,-cam1.y,-cam1.z,1);
	Vector4D u= up.cross(w);
	Vector4D v= w.cross(u);

	float tran[4][4]= 
	{{u.x,u.y,u.z,-(cam2.dot(u))},
	{v.x,v.y,v.z,-(cam2.dot(v))},
	{w.x,w.y,w.z,-(cam2.dot(w))},
	{0,0,0,1}};
	
	
	/*float veiw[4][4]=
	{{cos(the), -sin(phi)*sin(the),cos(phi)*sin(the),0},
	{0,cos(phi),sin(phi),0},
	{-sin(the),-sin(phi)*cos(the),cos(phi)*cos(the),0},
	{0,0,-d,1}};*/

	Matrix4D tran1(tran);

	tran1.standardise();

	return tran1;
}
/*
Matrix4D Matrix4D::veiwTrans(const Camera& cam,const Vector3D& upV)const
{
	Vector3D cam1 =cam.getDir();
	Vector4D cam2(cam.getPos()),up(upV);

	Vector4D w(-cam1.getX(),-cam1.getY(),-cam1.getZ(),1);
	Vector4D u= up.cross(w);
	Vector4D v= w.cross(u);

	float tran[4][4]= 
	{{u.getX(),u.getY(),u.getZ(),-(cam2.dot(u))},
	{v.getX(),v.getY(),v.getZ(),-(cam2.dot(v))},
	{w.getX(),w.getY(),w.getZ(),-(cam2.dot(w))},
	{0,0,0,1}};
	
	Matrix4D tran1(tran);

	tran1.standardise();

	return tran1;
}
*/
void Matrix4D::standardise()
{
	float modx= sqrt((matrix[0][0]*matrix[0][0])+(matrix[0][1]*matrix[0][1])+(matrix[0][2]*matrix[0][2]));
	float mody= sqrt((matrix[1][0]*matrix[1][0])+(matrix[1][1]*matrix[1][1])+(matrix[1][2]*matrix[1][2]));
	float modz= sqrt((matrix[2][0]*matrix[2][0])+(matrix[2][1]*matrix[2][1])+(matrix[2][2]*matrix[2][2]));

	for(int row=0; row<4;row++)
	{
		matrix[0][row] = (matrix[0][row]/modx);  
	}
	for(int row=0; row<4;row++)
	{
		matrix[1][row] = (matrix[1][row]/mody);  
	}
	for(int row=0; row<4;row++)
	{
		matrix[2][row] = (matrix[2][row]/modz);  
	}
	for(int row=0; row<4;row++)
	{
		matrix[3][row] = (matrix[3][row]);  
	}

}

void Matrix4D::trans(float x,float y ,float z)
{
	float mat1[4][4]= 
	{{1,0,0,x},
	{0,1,0,y},
	{0,0,1,z},
	{0,0,0,1}};

	Matrix4D mat2(mat1);
	*this=mat2;
}

void  Matrix4D::scale(float x,float y,float z)
{
	float mat1[4][4]= 
	{{x,0,0,0},
	{0,y,0,0},
	{0,0,z,0},
	{0,0,0,1}};

	Matrix4D mat2(mat1);
	*this=mat2;
}

Matrix4D Matrix4D::inverse()const
{
	float mat1[4][4]= 
	{{matrix[0][0],matrix[1][0],matrix[2][0],matrix[3][0],},
	{matrix[0][1],matrix[1][1],matrix[2][1],matrix[3][1]},
	{matrix[0][2],matrix[1][2],matrix[2][2],matrix[3][2]},
	{matrix[0][3],matrix[1][3],matrix[2][3],matrix[3][3]}};

	Matrix4D mat2(mat1);
	return mat2;

}

Matrix4D Matrix4D::persp(float fov,float asp1,float asp2,float near,float far)const
{
	float height, width, radian;

	radian= (fov*PI/180);
	height= (near*tan((radian/2)));
	width= height*(asp1/asp2);
	

	float mat1[4][4]= 
	{{(near/width),0,0,0},
	{0,(near/height),0,0},
	{0,0,(-far/(far-near)),((-far*near)/(far-near))},
	{0,0,-1,0}};

	Matrix4D mat2(mat1);
	return mat2;
}

Matrix4D Matrix4D::projectionX()const
{
	float mat1[4][4]= 
	{{0,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1}};

	Matrix4D proj(mat1);
	return proj;
}
Matrix4D Matrix4D::projectionY()const
{
	float mat1[4][4]= 
	{{1,0,0,0},
	{0,0,0,0},
	{0,0,1,0},
	{0,0,0,1}};

	Matrix4D proj(mat1);
	return proj;
}
Matrix4D Matrix4D::projectionZ()const
{
	float mat1[4][4]= 
	{{1,0,0,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,1}};

	Matrix4D proj(mat1);
	return proj;
}



Matrix4D::~Matrix4D(void)
{
}