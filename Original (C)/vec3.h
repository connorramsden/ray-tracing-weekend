#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>
using std::istream;
using std::ostream;

// Defining a float-random function here so that every class will inherit access
#define frand48() ((float)rand()/RAND_MAX)

// Simple Vector3 class
class vec3
{
public:
	// Default & Specialized Constructors
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	// Vec3 can store 3D position || color values
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	// Basic operator overloads
	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; };

	// "Complex" operator overloads
	inline vec3& operator+=(const vec3 & v2);
	inline vec3& operator-=(const vec3 & v2);
	inline vec3& operator*=(const vec3 & v2);
	inline vec3& operator/=(const vec3 & v2);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float squaredLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline void makeUnitVector();

	float e[3];
};

inline istream& operator>>(istream & is, vec3 & t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline ostream& operator<<(ostream & os, const vec3 & t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

// Normalizes / creates a unit vector
inline void vec3::makeUnitVector()
{
	float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vec3 operator+(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 & v1, const vec3 & v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 & v1, const vec3 & v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 & v1, const vec3 & v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 & v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(vec3 v, float t)
{
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator*(const vec3 & v, float t)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Dot Product calculation
inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

// Cross(Vector) Product Calcuation
inline vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3
	(
		(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
	);
}

inline vec3& vec3::operator+=(const vec3 & v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3 & v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline vec3& vec3::operator/=(const vec3 & v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t)
{
	float k = 1.0f / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

// Turns the passed vec3 into a unit vector
inline vec3 unitVector(vec3 v)
{
	return v / v.length();
}

#endif
