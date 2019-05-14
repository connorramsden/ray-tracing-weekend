#ifndef MATERIAL_H
#define MATERIAL_H

struct hitRecord;

#include "ray.h"
#include "hitable.h"

float schlick(float cosine, float refIdx)
{
	float rO = (1.0f - refIdx) / (1.0f + refIdx);
	rO = rO * rO;
	return rO * (1.0f - rO) * pow((1 - cosine), 5.0f);
}

bool refract(const vec3& v, const vec3& n, float niOverNt, vec3& refracted)
{
	vec3 uv = unitVector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);

	if (discriminant > 0.0f)
	{
		refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}

	return false;
}

vec3 reflect(const vec3 & v, const vec3 & n)
{
	return v - 2.0f * dot(v, n) * n;
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
	metal(const vec3& a, float f = 0.0f) : albedo(a)
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

		scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere());
		attenuation = albedo;

		return (dot(scattered.direction(), rec.normal) > 0.0f);
	}

	vec3 albedo;
	float fuzz;
};

class dielectric : public material
{
public:
	dielectric(float ri) : refIdx(ri) {}

	// Inherited via material
	virtual bool scatter(const ray& r_in, const hitRecord rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 outwardNormal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);

		float niOverNt;

		attenuation = vec3(1.0f, 1.0f, 1.0f);
		vec3 refracted;

		float reflectProb;
		float cosine;

		if (dot(r_in.direction(), rec.normal) > 0.0f)
		{
			outwardNormal = -rec.normal;
			niOverNt = refIdx;
			cosine = refIdx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		else
		{
			outwardNormal = rec.normal;
			niOverNt = 1.0f / refIdx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		if (refract(r_in.direction(), outwardNormal, niOverNt, refracted))
		{
			reflectProb = schlick(cosine, refIdx);
		}
		else
		{
			scattered = ray(rec.p, reflected);
			reflectProb = 1.0f;
		}

		if (frand48() < reflectProb)
		{
			scattered = ray(rec.p, reflected);
		}
		else
		{
			scattered = ray(rec.p, refracted);
		}

		return true;
	}

	float refIdx;
};

#endif