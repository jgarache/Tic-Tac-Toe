#pragma once
class Shape {

public:
	float x, y, r, g, b;
	char type;
	Shape();
	Shape(float x, float y, float r, float g, float b, char type);
	float getx();
	float gety();
	void setx();
	void sety();

};