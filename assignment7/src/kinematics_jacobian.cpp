#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
 
  Skeleton copy_sk = skeleton;

  Eigen::VectorXd xa = transformed_tips(skeleton, b);

  double h = 0.0000007;

  int bone = skeleton.size();
  for (int j = 0; j < skeleton.size(); j++) {
	  for (int a = 0; a < 3; a++) {
		  copy_sk[j].xzx(a) +=  h;
		  Eigen::VectorXd dxa = transformed_tips(copy_sk, b);  
		  copy_sk[j].xzx(a) -= h;
		  for (int i = 0; i < b.rows(); i++) {
			  for (int c = 0; c < 3; c++) {
				  J.row(i * 3 + c)(j * 3 + a) = (dxa.row(i)(c) - xa.row(i)(c)) / h;
				 //std::cout << "J " << i * 3 + c << "  " << j * 3 + a << " ==="<<J.row(i * 3 + c)(j * 3 + a) << "\n";
			  }
		  }		 
	  }
  }
  /////////////////////////////////////////////////////////////////////////////
}
