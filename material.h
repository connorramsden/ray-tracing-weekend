#ifndef MATERIAL_H
#define MATERIAL_H

struct hitRecord;

#include "ray.h"
#include "hitable.h"

#define frand48() ((float)rand()/RAND_MAX)

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 randomInUnitSphere()
{
	vec3 p;

	do
	{
		p = 2.0f * vec3(frand48(), frand48(), frand48()) - vec3(1.0f, 1.0f, 1.0f);
	} while (p.squaredLength() >= 1.0f);

	return p;
}

class material
{
public:
	virtual bool scatter(const ray& r_in, const hitRecord rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const vec3& a) : albedo(a) {}

	// Inherited via material
	virtual bool scatter(const ray& r_in, const hitRecord rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 target = rec.p + rec.normal + randomInUnitSphere();

		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;

		return true;
	}

	vec3 albedo;
};

class metal : public material
{
public:
	metal(const vec3& a, float f) : albedo(a)
	{
		if (f < 1.0f)
			fuzz = f;
		else
			fuzz = 1.0f;
	}

	// Inherited via material
	virtual bool scatter(const ray& r_in, const hitRecord rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unitVector(r_in.direction()), rec.normal);

		scattered = ray(rec.p, reflected + fuzz*randomInUnitSphere());
		attenuation = albedo;

		return (dot(scattered.direction(), rec.normal) > 0);
	}

	vec3 albedo;
	float fuzz;
};

#endif