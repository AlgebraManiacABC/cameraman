/*
Copyright (c) 2020 Chan Jer Shyan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>
#include <ostream>


template <class T>
class Vector2 {
public:
	T x, y;
	
	Vector2() :x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}
	
	Vector2& operator=(const Vector2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
	Vector2 operator+(Vector2& v) {
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(Vector2& v) {
		return Vector2(x - v.x, y - v.y);
	}
	
	Vector2& operator+=(Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2& operator-=(Vector2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	Vector2 operator+(double s) {
		return Vector2(x + s, y + s);
	}
	Vector2 operator-(double s) {
		return Vector2(x - s, y - s);
	}
	Vector2 operator*(double s) {
		return Vector2(x * s, y * s);
	}
	Vector2 operator/(double s) {
		return Vector2(x / s, y / s);
	}
	
	
	Vector2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	Vector2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	Vector2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	Vector2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}
	
	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}
	
	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	Vector2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	float dist(Vector2 v) const {
		Vector2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	Vector2 ortho() const {
		return Vector2(y, -x);
	}
	
	static float dot(Vector2 v1, Vector2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(Vector2 v1, Vector2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

	Vector2& normal() {
		std::swap(this->x, this->y);
		this->y = -this->y;
		return *this;
	}
	Vector2& abs() {
		this->x = std::abs(this->x);
		this->y = std::abs(this->y);
		return *this;
	}
	
	friend std::ostream& operator<< (std::ostream& out, const Vector2<T>& vector) {
		out << "Vector2(" << vector.x << ", " << vector.y << ")\n";
		return out;	
	}
	
};

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


#endif