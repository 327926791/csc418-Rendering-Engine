#include "linear_blend_skinning.h"
#include <iostream>

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	U = V;

  //std::cout << " linear blend skinning......................\n";
  //std::cout << V.rows() << " W:" << W.rows() << " w col:" << W.cols() << " skele:"<<skeleton.size()<<"T size:"<<T.size()<<"\n";
  //std::cout << "U size " << U.rows() << " " << U.cols() << "\n";

  //U[i] = U[i] + W[i, skeleton[j].weight_index] * T[j] * V[i];
  for (int i = 0; i < V.rows(); i++) {
	  //std::cout << "calculate U....."<<i<<"\n";
	  U.row(i)= Eigen::Vector3d(0, 0, 0);
	  Eigen::Vector4d x = Eigen::Vector4d(0, 0, 0, 0), v;
	  v = Eigen::Vector4d(V.row(i)[0], V.row(i)[1], V.row(i)[2], 1);

	  for (int j = 0; j<skeleton.size(); j++) {
		  // calculate T[j] * V[i]  ---> x
		  if (skeleton[j].weight_index >= 0) {
			  x = W.row(i)(skeleton[j].weight_index) * (T[j] * v);
			  U.row(i)(0) = U.row(i)(0) + x(0);
			  U.row(i)(1) = U.row(i)(1) + x(1);
			  U.row(i)(2) = U.row(i)(2) + x(2);
		  }
		  //std::cout << "weight index:" << skeleton[j].weight_index << "\n";
		  //std::cout << ".......linear result: " << U.row(i)[0] << " " << U.row(i)[1] << " " << U.row(i)[2] << "\n";
		 // std::cout << ".......one round done....\n";
	  }
	 // std::cout << ".......next round....\n";
  }
  
  /////////////////////////////////////////////////////////////////////////////
}
