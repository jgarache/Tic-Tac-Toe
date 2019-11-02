#include "Shape.h"

Shape::Shape() 
{
	this->x = 0.0;
	this->y = 0.0;

	this->r = 0.0;
	this->g = 0.0;
	this->b = 0.0;
	this->type = ' ';

}

Shape::Shape(float x, float y, float r, float g, float b, char type) 
{

	this->x = x;
	this->y = y;

	this->r = r;
	this->g = g; 
	this->b = b;

	this->type = type;

}

float Shape::getx()
{
	return this->x;
}

float Shape::gety() 
{
	return this->y;
}

void Shape::setx() 
{
	this->x = x;
}

void Shape::sety() 
{
	this->y = y;
}
