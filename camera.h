#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

constexpr auto M_PI = 3.14159265358979323846f;  // pi

class camera
{
public:
	camera(float vfov, float aspect) // vfov is a top to bottom in degrees
	{
		float theta = vfov * M_PI / 180.0f;
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;
		
		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0f);
		horizontal = vec3(2.0f*halfWidth, 0.0f, 0.0f);
		vertical = vec3(0.0f, 2.0f*halfHeight, 0.0f);
		origin = vec3(0.0f, 0.0f, 0.0f);
	}

	ray getRay(float u, float v)
	{
		return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

#endif
