#include "types.h"

//int8
TYPES::int8::int8(int x) {
	this->value = (signed char)x;
}
int TYPES::int8::get() {
	return (int)this->value;
}
void TYPES::int8::set(int x) {
	this->value = (signed char)x;
}

//uint
TYPES::uint8::uint8(unsigned int x) {
	this->value = (unsigned char)x;
}
unsigned int TYPES::uint8::get() {
	return (unsigned int)this->value;
}
void TYPES::uint8::set(unsigned int x) {
	this->value = (unsigned char)x;
}

//Color
TYPES::Color::Color() {}
TYPES::Color::Color(float r, float g, float b) {
	this->r = r / 255;
	this->g = g / 255;
	this->b = b / 255;
}

//point
TYPES::point::point() {}
TYPES::point::point(int x, int y) {
	this->x = x;
	this->y = y;
}
bool TYPES::point::operator==(const point &a) {
	return this->x == a.x && this->y == a.y;
}
bool TYPES::point::operator!=(const point &a) {
	return this->x != a.x || this->y != a.y;
}

//pointf
TYPES::pointf::pointf() {}
TYPES::pointf::pointf(float x, float y) {
	this->x = x;
	this->y = y;
}
bool TYPES::pointf::operator==(const pointf &a) {
	return this->x == a.x && this->y == a.y;
}
bool TYPES::pointf::operator!=(const pointf &a) {
	return this->x != a.x || this->y != a.y;
}