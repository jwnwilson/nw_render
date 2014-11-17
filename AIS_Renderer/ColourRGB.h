#pragma once

//Simple class does as explected
class ColourRGB
{
public:
	ColourRGB();
	//floats: red, green, blue.
	ColourRGB(float, float, float);
	ColourRGB	operator + (const ColourRGB&)const;
	ColourRGB	operator - (const ColourRGB&)const;
	ColourRGB	operator * (const ColourRGB&)const;
	ColourRGB   operator * (const float&)const;
	bool   operator ==(const ColourRGB&)const;
	bool   operator !=(const ColourRGB& c)const;
	//double check alpha
	void    setAlpha(float f){alpha=f;}

	float	getRed()const{return red;}
	float	getGreen()const{return green;}
	float	getBlue()const{return blue;}
	float   getAlpha()const{return alpha;}

	ColourRGB  modulate(const ColourRGB&)const;
	
	void scale(float);
	void clamp();

	~ColourRGB(void);

private:
	float red, green, blue, alpha;
};
