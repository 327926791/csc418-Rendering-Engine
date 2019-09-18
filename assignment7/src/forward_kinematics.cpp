#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
#include <iostream>

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	Eigen::Affine3d R, T1;

	T.resize(skeleton.size(), Eigen::Affine3d::Identity());

	for (int i = 0; i < skeleton.size(); i++) {
		if (skeleton[i].parent_index == -1) {   //root
			T[i]= Eigen::Affine3d::Identity();
		}
		else {
			Eigen::Affine3d R = euler_angles_to_transform(skeleton[i].xzx);
			T[i] = T[skeleton[i].parent_index] * skeleton[i].rest_T * R * skeleton[i].rest_T.inverse();
		}
	}

  /////////////////////////////////////////////////////////////////////////////
}
