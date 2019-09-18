#include "copy_skeleton_at.h"
#include <iostream>
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	Skeleton copy_sk = Skeleton(skeleton);
	//copy_sk.reserve(skeleton.size());

  for (int i = 0; i < skeleton.size(); i++) {
	  copy_sk[i].xzx = A.block(i * 3, 0, 3, 1);
  }

  return copy_sk;
  /////////////////////////////////////////////////////////////////////////////
}
