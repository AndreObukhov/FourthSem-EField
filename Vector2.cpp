#include "pch.h"

#include "Vector2.h"

Point::Point() {			//default
	x = 0;
	y = 0;
}
Point::Point(const sf::Vector2i& pos) {
	x = pos.x;
	y = pos.y;
}
Point::Point(const double& x1, const double& y1) {
	x = x1;
	y = y1;
}


Vector2::Vector2() {
	x = 0;
	y = 0;
	Start = { 0.0, 0.0 };
}

Vector2::Vector2(const Point& P1, const Point& P2) {
	x = P2.x - P1.x;
	y = P2.y - P1.y;
	Start = P1;
}

Vector2::Vector2(const Point& St, const double& x1, const double& y1) {
	Start = St;
	x = x1;
	y = y1;
}

Vector2 Vector2::operator*(const double& num) {
	return Vector2(Start, x * num, y * num);
}

void Vector2::Rotate(const double& angle) {
	double x_res = x * cos(angle) - y * sin(angle);
	double y_res = x * sin(angle) + y * cos(angle);
	x = x_res;
	y = y_res;
}

/*Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2(Start, (x + v.x), (y + v.y));
}

Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2(Start, (x - v.x), (y - v.y));
}*/

double Vector2::Length() {
	return sqrt(x * x + y * y);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.Start, lhs.x + rhs.x, lhs.y + rhs.y);
}