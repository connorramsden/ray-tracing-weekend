#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
	camera()
	{
		lowerLeftCorner = vec3(-2.0f, -1.0f, -1.0f);
		horizontal = vec3(4.0f, 0.0f, 0.0f);
		vertical = vec3(0.0f, 2.0f, 0.0f);
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
