#pragma once

#include "pch.h"
#include "SFML/Graphics.hpp"
#include <cmath>


struct Point {
	Point();
	Point(const sf::Vector2i& pos);
	Point(const double& x1, const double& y1);

	double x;
	double y;
};

struct Vector2 {
	Vector2();
	Vector2(const Point& P1, const Point& P2);
	Vector2(const Point& St, const double& x1, const double& y1);


	double Length();
	//Vector2 operator+(const Vector2& v) const;
	//Vector2 operator-(const Vector2& v) const;
	Vector2 operator *(const double& num);
	void Rotate(const double& angle);

	Point Start;
	double x;
	double y;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);