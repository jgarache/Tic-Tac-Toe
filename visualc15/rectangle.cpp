#include "rectangle.h"

rectangle::rectangle() {
	this->w = 0;
	this->h = 0;
}

rectangle::rectangle(float x, float y, float w, float h, float r, float g, float b)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;

}

bool rectangle::contains(float x, float y) {

	if (this->x <= x && x <= (this->x + this->w))
		if (this->y >= y && y >= (this->y - this->h))
			return true;
	return false;
}

float rectangle::getx() {
	return this->x;
}

float rectangle::gety() {
	return this->y;
}

float rectangle::getw() {
	return this->w;
}

float rectangle::geth() {
	return this->h;
}

void rectangle::setx() {
	this->x;
}

void rectangle::sety() {
	this->y;
}

void rectangle::setw() {
	this->w;
}

void rectangle::seth() {
	this->h;
}

rectangle::~rectangle() {
}