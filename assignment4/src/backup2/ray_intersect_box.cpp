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
	double x_min, y_min, z_min, x_max, y_max, z_max, xd, yd, zd, xe, ye, ze;
	double txmin, txmax, tymin, tymax, tzmin, tzmax;

	t = -1;
	x_min = box.min_corner(0);
	y_min = box.min_corner(1);
	z_min = box.min_corner(2);
	x_max = box.max_corner(0);
	y_max = box.max_corner(1);
	z_max = box.max_corner(2);

	xd = ray.direction(0);
	yd = ray.direction(1);
	zd = ray.direction(2);

	xe = ray.origin(0);
	ye = ray.origin(1);
	ze = ray.origin(2);

	if (xd>0) {
		txmin = (x_min - xe) / xd;
		txmax = (x_max - xe) / xd;
	}
	else {
		txmin = (x_max - xe) / xd;
		txmax = (x_min - xe) / xd;
	}

	if (yd>0) {
		tymin = (y_min - ye) / yd;
		tymax = (y_max - ye) / yd;
	}
	else {
		tymin = (y_max - ye) / yd;
		tymax = (y_min - ye) / yd;
	}

	if (zd>0) {
		tzmin = (z_min - ze) / zd;
		tzmax = (z_max - ze) / zd;
	}
	else {
		tzmin = (z_max - ze) / zd;
		tzmax = (z_min - ze) / zd;
	}

	if (txmin > tymax || tymin > txmax || 
		txmin > tzmax || tzmin > txmax )
		return false;

	if (tzmin > txmin)
		txmin = tzmin;
	if (tymin > txmin)
		txmin = tymin;

	if (txmin > min_t && txmin < max_t) {
		t = txmin;
		return true;
	}
	else
		return false;
  ////////////////////////////////////////////////////////////////////////////
}
