#include <string>
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)

#include "camera.h"
#include "sphere.h"
#include "hitableList.h"
#include "float.h"

using namespace std;

vec3 randomInUnitSphere()
{
	vec3 p;

	do
	{
		p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
	} while (p.squaredLength() >= 1.0f);

	return p;
}

// Hard-coded color-from-ray calculation
vec3 color(const ray& r, hitable* world)
{
	hitRecord rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + randomInUnitSphere();

		return 0.5f* color(ray(rec.p, target - rec.p), world);
	}
	else
	{
		vec3 unitDirection = unitVector(r.direction());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	srand48(time(0));

	// Our image is 200x100 pixels
	int nX = 200;
	int nY = 100;
	int nS = 100;

	// Creates a ppm file
	ofstream output("my_image.ppm");

	if (output.good())
	{
		output << "P3\n" << nX << " " << nY << "\n255\n";

		hitable* list[2];

		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);

		hitable * world = new hitableList(list, 2);

		camera cam;

		for (int j = nY - 1; j >= 0; j--)
		{
			for (int i = 0; i < nX; i++)
			{
				vec3 col(0, 0, 0);

				for (int s = 0; s < nS; s++)
				{
					float u = float(i + drand48()) / float(nX);
					float v = float(j + drand48()) / float(nY);

					ray r = cam.getRay(u, v);
					vec3 p = r.pointAtParameter(2.0f);
					col += color(r, world);
				}

				col /= float(nS);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

				int iR = int(255.99f * col[0]);
				int iG = int(255.99f * col[1]);
				int iB = int(255.99f * col[2]);

				output << iR << " " << iG << " " << iB << "\n";
			}
		}
	}

	output.close();

	system("pause");
	return 0;
}
