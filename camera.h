#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

constexpr auto M_PI = 3.14159265358979323846f;  // pi

class camera
{
public:
	camera(vec3 lookFrom, vec3 lookAt, vec3 vUp, float vfov, float aspect) // vfov is a top to bottom in degrees
	{
		vec3 u, v, w;
		
		float theta = vfov * M_PI / 180.0f;
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;

		origin = lookFrom;
		w = unitVector(lookFrom - lookAt);
		u = unitVector(cross(vUp, w));
		v = cross(w, u);

		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
		horizontal = 2.0f * halfWidth * u;
		vertical = 2 * halfHeight * v;
	}

	ray getRay(float s, float t)
	{
		return ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

#endif
