#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <iostream>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
   double dis = 0;

  I = -1;
  sqrD = 999999;

  //std::cout << points.rows() << "\n";
  for (int i = 0; i<points.rows(); i++) {
	  //std::cout << points(i, 0) << " " << points(i, 1) << " " << points(i, 2) << "\n";
	  dis = pow((points(i, 0) - query[0]), 2) + pow((points(i, 1) - query[1]), 2) + pow((points(i, 2) - query[2]), 2);
	  if (dis<sqrD)
	  {
		  sqrD = dis;
		  I = i;
	  }
  }
  return;

  ////////////////////////////////////////////////////////////////////////////
}
