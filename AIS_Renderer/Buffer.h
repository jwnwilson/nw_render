#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <class T>
class Buffer
{
public:
	Buffer();
	Buffer(int,int);
	~Buffer();

	void setPix(int,int,T);
	void setPix(int,T);
	void setAll(T);
	T getPix(int,int)const;
	T getPix(int)const;

	void resize(int);
	void resize(int,int);

	T* getBuffPtr();
	void setHeight(int h){height=h;}
	void setWidth(int w){width=w;}
	int getHeight()const{return height;}
	int getWidth()const{return width;}
	int getSize()const{return buffer.size();}
	
private:
	int height,width;
	vector <T> buffer;
};

template <class T>
Buffer<T>::Buffer(void)
{
	buffer.resize(1);
	width=1;
	height=1;

}
template <class T>
Buffer<T>::Buffer(int m,int n)
{
	buffer.resize(m*n);
	width=m;
	height=n;
}
template <class T>
Buffer<T>::~Buffer(void)
{
}
template <class T>
T* Buffer<T>::getBuffPtr()
{
	T* Buffptr = &buffer[0];
	return Buffptr;
}
template <class T>
void Buffer<T>::setPix(int m, int n, T data)
{
	buffer[(width*n)+m]= data;
}
template <class T>
void Buffer<T>::setAll(T n)
{
	for(int i=0;i<buffer.size();i++)
	{
		buffer[i]=n;
	}
}
template <class T>
void Buffer<T>::setPix(int m, T data)
{
	buffer[m]= data;
}
template <class T>
T Buffer<T>::getPix(int m)const
{
	return buffer[m];
}
template <class T>
T Buffer<T>::getPix(int m,int n)const
{
	return buffer[(width*n)+m];
}
template <class T>
void Buffer<T>::resize(int m)
{
	buffer.resize(m);
}
template <class T>
void Buffer<T>::resize(int m,int n)
{
	buffer.resize(m*n);
	height=n;
	width=m;
}