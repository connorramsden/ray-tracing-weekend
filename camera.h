#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

constexpr auto M_PI = 3.14159265358979323846f;  // pi

vec3 randomInUnitDisk()
{
	vec3 p;

	do
	{
		p = 2.0f * vec3(frand48(), frand48(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0f);

	return p;
}

class camera
{
public:
	camera(vec3 lookFrom, vec3 lookAt, vec3 vUp, float vfov, float aspect, float aperture, float focusDist) // vfov is a top to bottom in degrees
	{
		lensRadius = aperture / 2;

		float theta = vfov * M_PI / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;

		origin = lookFrom;
		w = unitVector(lookFrom - lookAt);
		u = unitVector(cross(vUp, w));
		v = cross(w, u);

		lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
		horizontal = 2.0f * halfWidth * focusDist * u;
		vertical = 2 * halfHeight * focusDist * v;
	}

	ray getRay(float s, float t)
	{
		vec3 rd = lensRadius * randomInUnitDisk();
		vec3 offset = u * rd.x() + v * rd.y();

		return ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lensRadius;
};

#endif
