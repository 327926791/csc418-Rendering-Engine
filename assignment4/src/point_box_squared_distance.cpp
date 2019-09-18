#include "point_box_squared_distance.h"
#include <iostream>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
	double x0, y0, z0, x, y, z, dis;

//std::cout << query << " " << box.max_corner << "|" << box.min_corner << "\n";
	x0 = query[0];
	y0 = query[1];
	z0 = query[2];

	x = (x0 < box.min_corner[0]) ? box.min_corner[0] : (x0 > box.max_corner[0]) ? box.max_corner[0] : x0;
	y = (y0 < box.min_corner[1]) ? box.min_corner[1] : (y0 > box.max_corner[1]) ? box.max_corner[1] : y0;
	z = (z0 < box.min_corner[2]) ? box.min_corner[2] : (z0 > box.max_corner[2]) ? box.max_corner[2] : z0;

	dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
//std::cout << dis << "\n";
	return dis;

  ////////////////////////////////////////////////////////////////////////////
}
