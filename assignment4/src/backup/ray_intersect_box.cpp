#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double txmin, txmax, tymin, tymax, tzmin, tzmax, tmin, tmax;
	double xmin, xmax, ymin, ymax, zmin, zmax, divx;
	double xe, xd, ye, yd, ze, zd;
	xmin = box.min_corner[0];
	xmax = box.max_corner[0];
	ymin = box.min_corner[1];
	ymax = box.max_corner[1];
	zmin = box.min_corner[2];
	zmax = box.max_corner[2];
	xe = ray.origin[0];
	xd = ray.direction[0];
	ye = ray.origin[1];
	yd = ray.direction[1];
	ze = ray.origin[2];
	zd = ray.direction[2];


	/*txmin = (xmin - xe) / xd;
	txmax = (xmax - xe) / xd;
	tymin = (xmin - ye) / yd;
	tymax = (xmax - ye) / yd;
	tzmin = (xmin - ze) / zd;
	tzmax = (xmax - ze) / zd;*/

	//algo reference to http://www.cs.utah.edu/~awilliam/box/box.pdf

	divx = 1 / xd;

	if (divx >= 0) {
		tmin = (xmin - xe) * divx;
		tmax = (xmax - xe) * divx;
	}
	else {		
		tmin = (xmax - xe) * divx;
		tmax = (xmin - xe) * divx;
	}
	if (yd >= 0) {
		tymin = (ymin - ye) / yd;
		tymax = (ymax - ye) / yd;
	}
	else {
		tymin = (ymax - ye) / yd;
		tymax = (ymin - ye) / yd;
	}
	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
			tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	if (zd >= 0) {
		tzmin = (zmin - ze) / zd;
		tzmax = (zmax - ze) / zd;
	}
	else {
		tzmin = (zmax - ze) / zd;
		tzmax = (zmin - ze) / zd;
	}
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return ((tmin < max_t) && (tmax > min_t));
  ////////////////////////////////////////////////////////////////////////////
}
