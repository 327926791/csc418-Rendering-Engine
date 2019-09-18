#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
	d = p-q;
	max_t = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
	//max_t = (p - d) / d;
	////////////////////////////////////////////////////////////////////////////
}
