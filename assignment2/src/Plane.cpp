#include "Plane.h"
#include "Ray.h"
#include "iostream"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, product;
	vp1 = normal[0];
	vp2 = normal[1];
	vp3 = normal[2];
	n1 = point[0];
	n2 = point[1];
	n3 = point[2];
	v1 = ray.direction[0];
	v2 = ray.direction[1];
	v3 = ray.direction[2];
	m1 = ray.origin[0];
	m2 = ray.origin[1];
	m3 = ray.origin[2];
	product = v1 * vp1 + v2 * vp2 + v3 * vp3;

	if (product == 0) {
		return false;
	}
	else {
		t = ((n1 - m1)*vp1 + (n2 - m2)*vp2 + (n3 - m3)*vp3) / product;
		if (t < min_t)
			return false;
		else {
			//std::cout << normal[0] <<" " << normal[1] << " " << normal[2] << " " << std::endl;
			n = normal;
			//std::cout << " true. t= " << t << std::endl;
			return true;
		}
	}

  ////////////////////////////////////////////////////////////////////////////
}

