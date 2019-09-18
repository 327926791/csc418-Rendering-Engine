#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <iostream>
bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = 0;
  hit_f = 0;

  Eigen::Vector3d A[3];
  double min_hit_t = max_t, t;
  int inV;


  for (int i = 0; i < F.rows(); i++) {
	  for (int k = 0; k < 3; k++) {
		  A[k]=V.row(F(i, k));
	  }

	//  std::cout << A[0] <<"|"<< A[1]<<"|" << A[2] << "\n";
	 // std::cout << "ray is: " << ray.direction << "\n";
	  if (ray_intersect_triangle(ray, A[0], A[1], A[2], min_t, max_t, t)) {
		//  std::cout << "hit!!!!!!\n";
		  if (t < min_hit_t) {
			  min_hit_t = t;
			  hit_f = i;
		  }
	  }
  }

  if (min_hit_t != max_t) {
	  hit_t = min_hit_t;
	  return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
