#include "cube.h"
#include <vector>
#include <iostream>

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  ////Hint:
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  std::vector<int> v1 = { 0,1 }, v2 = { 0,-1 };

  // cube vetex 3D coordinates
  for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 2; j++) {
		  for (int k = 0; k < 2; k++) {
			  V(i * 4 + j * 2 + k, 0) = v1[i];
			  V(i * 4 + j * 2 + k, 1) = v2[j];
			  V(i * 4 + j * 2 + k, 2) = v1[k];
		  }
	  }
  }

// cube face to vetex mapping 
F << 2, 1, 5, 6,
6, 5, 7, 8,
8, 7, 3, 4,
4, 3, 1, 2,
2, 6, 8, 4,
1, 3, 7, 5;

// 2D texture coordinates
 UV << 0, 0.5,
	  0, 0.25,
	  0.25, 0.75,
	  0.25, 0.5,
	  0.25, 0.25,
	  0.25, 0,
	  0.5, 0.75,
	  0.5, 0.5,
	  0.5, 0.25,
	  0.5, 0,
	  0.75, 0.5,
	  0.75, 0.25,
	  1, 0.5,
	  1, 0.25;

 //Face to texture vertex mapping
  UF << 4,5,9,8,
	  8, 9, 12, 11,
	  11, 12, 14, 13,
	  1, 2, 5, 4,
	  4,8,7,3,
	  5, 6, 10, 9;

  // face normals
  NV << 0, 1, 0,
	  1, 0, 0,
	  0, -1, 0,
	  -1, 0, 0,
	  0, 0, 1,
	  0, 0, -1;

  // each vertex normal 
  NF << 1, 1, 1, 1,
	  2, 2, 2, 2,
	  3, 3, 3, 3,
	  4, 4, 4, 4,
	  5, 5, 5, 5,
	  6, 6, 6, 6;
}
