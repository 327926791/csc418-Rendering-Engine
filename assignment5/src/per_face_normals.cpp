#include "per_face_normals.h"
#include "triangle_area_normal.h"
#include <iostream>


void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  N = Eigen::MatrixXd::Zero(F.rows(),F.cols());
  Eigen::RowVector3d a, b, c, per_face_n;

  for (int i = 0; i < F.rows(); i++) {
	  for (int j = 0; j < 3; j++) {
		  a(j) = V(F(i, 0), j);
		  b(j) = V(F(i, 1), j);
		  c(j) = V(F(i, 2), j);
	  }

	  per_face_n = triangle_area_normal(a, b, c);
//	  std::cout << "per face normal:" << per_face_n << "\n";
	  per_face_n = per_face_n.normalized();
	  N(i,0)= per_face_n(0);
	  N(i,1)= per_face_n(1);
	  N(i,2)= per_face_n(2);
  }
  ////////////////////////////////////////////////////////////////////////////
}
