#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class hitableList : public hitable
{
public:
	hitableList() {}
	hitableList(hitable** l, int n) { list = l; listSize = n; }

	virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;

	hitable** list;
	int listSize;
};

bool hitableList::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const
{
	hitRecord tempRec;

	bool hitAnything = false;
	float closestSoFar = t_max;

	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->hit(r, t_min, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

#endif
