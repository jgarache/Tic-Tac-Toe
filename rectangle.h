#pragma once
#include "Shape.h"
class rectangle :
	public Shape 
{
public:
	float w, h;

	rectangle();
	rectangle(float x, float y, float w, float h, float r, float g, float b);

	bool contains(float x, float y);

	float getx();
	float gety();
	float geth();
	float getw();

	void setx();
	void sety();
	void seth();
	void setw();
	
	~rectangle();

};

