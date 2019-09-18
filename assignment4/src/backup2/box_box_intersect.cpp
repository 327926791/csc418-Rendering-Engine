#include "box_box_intersect.h"
#include "ray_intersect_box.h"
#include "Ray.h"
#include <vector>


bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	if (A.min_corner(0) > B.max_corner(0) || A.max_corner(0) < B.min_corner(0) || A.min_corner(1) > B.max_corner(1) || A.max_corner(1) < B.min_corner(1))
		return false;
	else if (A.min_corner(2) > B.max_corner(2) || A.max_corner(2) < B.min_corner(2))
		return false;
	else
		return true;

  ////////////////////////////////////////////////////////////////////////////
}

