#include "transformed_tips.h"
#include "forward_kinematics.h"
#include <iostream>

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;
	Eigen::VectorXd tips = Eigen::VectorXd(3 * b.rows());

	forward_kinematics(skeleton, T);

	// compute position of rest bone's tail to pose bone's position
	for (int i = 0; i < b.rows(); i++) {
		int index = b.row(i)(0);
		Eigen::Vector4d x = T[index] * skeleton[index].rest_T * Eigen::Vector4d(skeleton[index].length, 0, 0, 1);
		
		tips[i *3] = x[0] / x[3];
		tips[i *3+1] = x[1] / x[3];
		tips[i *3+2] = x[2] / x[3];
	}
	
  return tips ;
  /////////////////////////////////////////////////////////////////////////////
}
