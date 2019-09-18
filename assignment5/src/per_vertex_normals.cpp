#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
#include <vector>

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  Eigen::RowVector3d normal;
  std::vector<std::vector<int>> VF;
  Eigen::RowVector3d a, b, c;

  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int i = 0; i < V.rows(); i++) {
	  normal = Eigen::Vector3d(0, 0, 0);
	  for (int j = 0; j < VF[i].size(); j++) {
		  for (int k = 0; k < 3; k++) {
			  a(k) = V(F(VF[i][j], 0), k);
			  b(k) = V(F(VF[i][j], 1), k);
			  c(k) = V(F(VF[i][j], 2), k);
		  }
	      normal = normal + triangle_area_normal(a, b, c);
	  }
	  normal = normal.normalized(); 
	  N(i, 0) = normal(0);
	  N(i, 1) = normal(1);
	  N(i, 2) = normal(2);
  }
  ////////////////////////////////////////////////////////////////////////////
}
