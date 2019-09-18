#include "triangle_area_normal.h"
#include <Eigen/Geometry>
#include <iostream>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
	Eigen::Vector3d U, V,A;
	double area;
	Eigen::RowVector3d N;

	U = b - a;
	V = c - a;
	//calculate triangle area
	A = U.cross(V);
	area = sqrt(A.dot(A)) / 2;
//	std::cout << "triangle area: " << area<<"\n";
//	std::cout << "U, V, A:" << U << " " << V << " " << A<<"\n";

	// calcuate normal vector
	N.row(0)[0] = U(1) * V(2) - U(2) * V(1);
	N.row(0)[1] = U(2) * V(0) - U(0) * V(2);
	N.row(0)[2] = U(0) * V(1) - U(1) * V(0);

//	std::cout << "  calcuate from per area normal:" << N(0) << " " << N(1) << " " << N(2) << "\n";
	// weighted by area
	N = area * N.normalized();
//std::cout << "normal per area:"<<N << "\n";
	return N;

  ////////////////////////////////////////////////////////////////////////////
}

