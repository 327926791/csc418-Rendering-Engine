#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d R;
	R = in - 2 * (in.dot(n)) * n;
	R = R / sqrt(R.dot(R));

  return R;
  ////////////////////////////////////////////////////////////////////////////
}
