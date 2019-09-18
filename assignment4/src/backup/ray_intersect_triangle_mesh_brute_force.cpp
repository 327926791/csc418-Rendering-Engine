#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

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
//	V[0]->	
	Eigen::Vector3d V1, V2, V3;
	for (int n = 0; n < F.rows(); n++) {
		V1 = V.row(F(n, 0));
		V2 = V.row(F(n, 1));
		V3 = V.row(F(n, 2));
		if (ray_intersect_triangle(ray, V1, V2, V3, min_t, max_t, hit_t)) {
			hit_f = n;
			return true;
		}

	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
