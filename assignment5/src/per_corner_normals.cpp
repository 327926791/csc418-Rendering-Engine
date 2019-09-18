#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <vector>
#include <cmath>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
	Eigen::RowVector3d a, b, c;
	std::vector<std::vector<int>> VF;
	float deviate;

  N = Eigen::MatrixXd::Zero(F.rows()*3,3);


  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  Eigen::Vector3d  nn, cur_face_normal, corner_normal;
  nn = Eigen::Vector3d(0, 0, 0);

  vertex_triangle_adjacency(F,V.rows(), VF);

  for (int i = 0; i < F.rows(); i++) {
	  // calculate current surface normal
	  for (int j = 0; j < 3; j++) {
		  a(j) = V(F(i, 0), j);
		  b(j) = V(F(i, 1), j);
		  c(j) = V(F(i, 2), j);
	  }
	  cur_face_normal = triangle_area_normal(a, b, c);
	  cur_face_normal = cur_face_normal.normalized();
	  
	  for (int j = 0; j < F.cols(); j++) {
		  // calculate per-corner normal, ignore the face normal whose normal deviate is large than thresdhold
		  corner_normal = Eigen::Vector3d(0, 0, 0);
		  nn = Eigen::Vector3d(0, 0, 0);
		  for (int m = 0; m < VF[F(i, j)].size(); m++) {
//			  std::cout << ".......check each face.......\n";
			  for (int k = 0; k <3; k++) {
				  a(k) = V(F(VF[F(i, j)][m], 0), k);
				  b(k) = V(F(VF[F(i, j)][m], 1), k);
				  c(k) = V(F(VF[F(i, j)][m], 2), k);
			  }
			  nn = triangle_area_normal(a, b, c);
//std::cout << "..sub face:" << VF[F(i,j)][m] << " normal is:" << nn << "\n";
			  nn = nn.normalized(); 

			  // calcuate the deviate between this face normal and average normal
			  deviate = nn.dot(cur_face_normal);  //nav /sqrt(nv * av) ;
			  deviate = 180 * acos(abs(deviate)) / 3.1415926;
//std::cout << "deviate:" << deviate << " acos(deviate): " << acos(deviate) << "   threshold:" << corner_threshold << "\n";

			  // if the deviate is less than threshold
			  if (deviate  < corner_threshold) {
				  corner_normal += nn;
			  }
		  }
		  corner_normal.normalize();
//			  std::cout << "per corner:" << corner_normal(0) << " " << corner_normal(1) << " " << corner_normal(2) << "\n";
		  N(i * 3 + j, 0) = corner_normal(0);
		  N(i * 3 + j, 1) = corner_normal(1);
		  N(i * 3 + j, 2) = corner_normal(2);
	  }
  }

  return;
  ////////////////////////////////////////////////////////////////////////////
}
