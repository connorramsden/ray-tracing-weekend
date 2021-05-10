#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Basic Ray class
class ray
{
public:
	// Default & Specialized Constructors
	ray() {}
	ray(const vec3& a, const vec3& b) { A = a; B = b; }

	// Returns vec3 matrices
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }

	// Creates a ray at origin A and points towards position B by parameter t
	vec3 pointAtParameter(float t) const { return A + t * B; }

	vec3 A;
	vec3 B;
};

#endif
