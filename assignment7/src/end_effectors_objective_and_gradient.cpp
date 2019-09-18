#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	//for (int i = 0; i < skeleton.size(); i ++) {
	//	std::cout << "orignal angel:" << skeleton[i].xzx(0) << " " << skeleton[i].xzx(1) << " " << skeleton[i].xzx(2) << "\n";
	//}

  f = [&](const Eigen::VectorXd & A)->double
  {
	 //std::cout << " calculate energy...."<<xb0.rows()<<" "<<b.rows()<<"\n";
	  // copy eular angle in A to copy_sk
	  //for (int i = 0; i < skeleton.size(); i++) {
		//  std::cout << "orignal angel:" << skeleton[i].xzx(0) << " " << skeleton[i].xzx(1) << " " << skeleton[i].xzx(2) << "\n";
	  //}
	  Skeleton copy_sk = copy_skeleton_at(skeleton, A);

	  // calculate x(a) with eular angle of A
	  Eigen::VectorXd xa = transformed_tips(copy_sk, b);

	  // calculate the sum of (x(a) - xb0) ^2
	  double total_energy;

	  for (int i = 0; i < b.rows(); i++) {
		  double dis = 0;
		  double min_energy = 99999;

		  /*
		  for (int j = 0; j < xb0.rows(); j = j + 3) {
			  //std::cout << xb0.row(j)(0) << "  "<<xa.row(i)(0)<<"\n";
			  //std::cout << "j " << j << "\n";
			  dis = pow((xa.row(i)(0) - xb0.row(j)(0)), 2) +
				  pow((xa.row(i)(1) - xb0.row(j + 1)(0)), 2) +
				  pow((xa.row(i)(2) - xb0.row(j + 2)(0)), 2);
		  
		      if (dis < min_energy)
			      min_energy = dis;
	      }*/
		  min_energy = pow((xa.row(i)(0) - xb0.row(i*3)(0)), 2) +
			  pow((xa.row(i)(1) - xb0.row(i*3 + 1)(0)), 2) +
			  pow((xa.row(i)(2) - xb0.row(i*3 + 2)(0)), 2);

		  total_energy = total_energy + min_energy;
	  }
    return total_energy;
  };

  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
	  Eigen::VectorXd grad = Eigen::VectorXd::Zero(skeleton.size() * 3);
	  Eigen::VectorXd grad1 = Eigen::VectorXd::Zero(skeleton.size() * 3);
	  Eigen::VectorXd E = Eigen::VectorXd(b.size() * 3);
	  double h = 0.0000007;
	  Eigen::MatrixXd J; // = Eigen::MatrixXd(b.size * 3, skeleton.size() * 3);
	  //std::cout << "------gradient------------------"<<b.rows()<<"\n";
	  // copy eular angle in A to copy_sk
	  Skeleton copy_sk = copy_skeleton_at(skeleton, A);
	  kinematics_jacobian(copy_sk, b, J);

	  // calculate x(a) with eular angle of A
	  Eigen::VectorXd xa = transformed_tips(copy_sk, b);

	  double min_de0=9999, min_de1=9999, min_de2=9999, de0, de1, de2;
	  for (int i = 0; i < b.rows(); i++) {
		  min_de0 = min_de1 = 9999;
		 // for (int j = 0; j < xb0.size(); j = j + 3) {
			  de0 = abs(xa.row(i)(0) - xb0.row(i*3)(0));
			  de1 = abs(xa.row(i)(1) - xb0.row(i*3+ 1)(0));
			  de2 = abs(xa.row(i)(2) - xb0.row(i*3 + 2)(0));
		 
		      min_de0 = (de0 < min_de0 ? de0 : min_de0);
		      min_de1 = (de1 < min_de1 ? de1 : min_de1);
		      min_de2 = (de2 < min_de2 ? de2 : min_de2);
	     // }

		  E.row(b.rows()-1-i)(0) = 2 * min_de0 * h;
		  E.row(b.rows() - 1 - i)(1) = 2 * min_de1 * h;
		  E.row(b.rows() - 1 - i)(2) = 2 * min_de2 * h;
	  }
	  grad = 180 *  J.transpose() * E  ;

	  
	  for (int i = 0; i < grad.rows()/3; i++) {
		  grad1.row(i*3) = grad.row(grad.rows()-3-i*3);
		  grad1.row(i*3+1) = grad.row(grad.rows()-3-i*3+1);
		  grad1.row(i*3+2) = grad.row(grad.rows()-3-i*3+2);
		  //grad1.row(i)(1) = grad.row(skeleton.size()*3 - 3 - i)(1);
		  //grad1.row(i)(2) = grad.row(skeleton.size()*3- 3 - i)(2);
	  } 
	  
	  //for (int i = 0; i < grad.rows(); i ++)
		//  std::cout << grad.row(i)<<" -----"<<grad1.row(i)<<"\n";

	//	  std::cout << "bone " << i / 3 << ":" << grad1.row(i)(0) << " " << grad1.row(i)(1) << " " << grad1.row(i)(2) << "\n";
	  //}
	  
	  return grad1;
  };

  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
	//std::cout << "project eular angle \n";
	for (int i = 0; i < A.size(); i=i+3) {
		A.row(i)(0) = std::fmod(A.row(i)(0), 360);
		A.row(i+1)(0) = std::fmod(A.row(i)(1), 360);
		A.row(i+2)(0) = std::fmod(A.row(i)(2), 360);

		if (A.row(i)(0) > skeleton[i/3].xzx_max(0))
			A.row(i)(0) = skeleton[i/3].xzx_max(0);
		else if (A.row(i)(0) < skeleton[i/3].xzx_min(0))
			A.row(i)(0) = skeleton[i/3].xzx_min(0);

		if (A.row(i+1)(0) > skeleton[i/3].xzx_max(1))
			A.row(i+1)(0) = skeleton[i/3].xzx_max(1);
		else if (A.row(i+1)(0) < skeleton[i/3].xzx_min(1))
			A.row(i+1)(0) = skeleton[i/3].xzx_min(1);

		if (A.row(i+2)(0) > skeleton[i/3].xzx_max(2))
			A.row(i+2)(0) = skeleton[i/3].xzx_max(2);
		else if (A.row(i+2)(0) < skeleton[i/3].xzx_min(2))
			A.row(i+2)(0) = skeleton[i/3].xzx_min(2);
	}
  };
  /////////////////////////////////////////////////////////////////////////////
}
