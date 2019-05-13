#include <string>
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define srand48(x) srand((int)(x))

#include "sphere.h"
#include "hitableList.h"
#include "float.h"
#include "camera.h"
#include "material.h"

using namespace std;

// Hard-coded color-from-ray calculation
vec3 color(const ray& r, hitable* world, int depth)
{
	hitRecord rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
			return vec3(0.0f, 0.0f, 0.0f);
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


		camera cam(90.0f, float(nX) / float(nY));
		float R = cos(M_PI / 4.0f);

		hitable * list[2];

		list[0] = new sphere(vec3(-R, 0.0f, -1.0f), R, new lambertian(vec3(0.0f, 0.0f, 1.0f)));
		list[1] = new sphere(vec3(R, 0.0f, -1.0f), R, new lambertian(vec3(1.0f, 0.0f, 0.0f)));

		hitable * world = new hitableList(list, 2);

		for (int j = nY - 1; j >= 0; j--)
		{
			for (int i = 0; i < nX; i++)
			{
				vec3 col(0.0f, 0.0f, 0.0f);

				for (int s = 0; s < nS; s++)
				{
					float u = float(i + frand48()) / float(nX);
					float v = float(j + frand48()) / float(nY);

					ray r = cam.getRay(u, v);
					vec3 p = r.pointAtParameter(2.0f);
					col += color(r, world, 0);
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
