#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <iostream>
#include <vertex_triangle_adjacency.h>

// given 4 corner points, calcuate center point position
Eigen::Vector3d calcuate_face_center(Eigen::Vector3d a, Eigen::Vector3d b, Eigen::Vector3d c, Eigen::Vector3d d) {
	Eigen::Vector3d new_point=Eigen::Vector3d(0,0,0);

	for (int i = 0; i < 3; i++) {
			new_point(i) = a(i)+b(i)+c(i)+d(i);
	}
	return new_point/4;
}


void do_catmull_clark(const Eigen::MatrixXd & V,
	const Eigen::MatrixXi & F,
	Eigen::MatrixXd & SV,
	Eigen::MatrixXi & SF) {

  //SV = Eigen::MatrixXd::Zero();
 // SF = Eigen::MatrixXi::Zero();
  SV = V;
  SF = F;

  SF.resize(F.rows() * 4, 4);
  Eigen::MatrixXi FC, FE;
  Eigen::Vector3d p1, p2, p3, p4;
  std::vector<std::vector<int>> VF, SVF;

  Eigen::Vector3d new_point;
  new_point(0) = 0;
  new_point(1) = 0;
  new_point(2) = 0;

  FC.resize(F.rows(),1);
  FE.resize(F.rows(), 4);
  FE = Eigen::MatrixXi::Zero(F.rows(),4);
  FC = Eigen::MatrixXi::Zero(F.rows(),1);

  // calcuate VF:  which faces are adjacent with a vetex
  vertex_triangle_adjacency(F, V.rows(), VF);

  // loop to calcuate each face's center, neighbour faces' center and edge center
  for (int i = 0; i < F.rows(); i++) {
      // 1. get 4 corner positions
	  for (int j = 0; j < 3; j++) {
		  p1(j) = SV(F(i, 0), j);
		  p2(j) = SV(F(i, 1), j);
		  p3(j) = SV(F(i, 2), j);
		  p4(j) = SV(F(i, 3), j);
	  }

	  // 2. calculate center position
	  new_point = calcuate_face_center(p1,p2,p3,p4);

	  // 3. extend SV matrix 
	  int ind = SV.rows();
	  SV.conservativeResize(ind + 1, 3);

	  // 4. add the center vetex to SV, index is ind
	  SV(ind, 0) = new_point(0);
	  SV(ind, 1) = new_point(1);
	  SV(ind, 2) = new_point(2);

	  // 5. add mapping vetex index to Face-to-center matrix FC
	  FC(i,0) = ind;

//std::cout << SV(FC(i), 0) << " " << SV(FC(i), 1) << " " << SV(FC(i), 2) << "\n";
  }
 
  
  //..............calcuate 4 edges' center points...............
  for (int i = 0; i < F.rows(); i++) {
//	  std::cout << "\nface " << i << " 's edge center====\n" ;
	  for (int k = 0; k < 4; k++) {
		  int ind;
		  std::vector<int> f1, f2;

		  f1 = VF[F(i, k)];               //current face's corner point k's adjacent faces
		  f2 = VF[F(i, (k + 1) % 4)];     //current face's corner point k+1's adjacent faces

		  // get the neighbour face with edge (k, k+1)
		  int ff;
		  for (int w = 0; w < f1.size(); w++) {
			  for (int u = 0; u < f2.size(); u++) {
				  if (f1[w] == f2[u] && f1[w] != i) {
					  // find the neighbour face index
					  ff = f1[w];
					  break;
				  }
			  }
		  }
		  
		  // calcuate edges' center point
//std::cout << " edge center by cal:" << new_point(0) << " " << new_point(1) << " " << new_point(2) << "\n";

		  // check if edges center has already been calculated
		  int e1=-1, e2=-1;
		  for (int ee = 0; ee < 4; ee++) {
			  if (FE(ff, ee) == 0)
				  continue;
			  if (F(ff, ee) == F(i, k) || F(ff, ee) == F(i, (k + 1) % 4)) {
				  e1 = ee;
				  if (F(ff, ee + 1) == F(i, k) || F(ff, ee + 1) == F(i, (k + 1) % 4)) {
					  FE(i, k) = FE(ff, e1);
					  e2 = ee + 1;
				  }
				  else {
					  FE(i, k) = FE(ff, 3);
					  e2 = 3;
				  }
				  break;
			  }
		  }
		  // if not, calculate edge center
		  if (e1 == -1) {
			  for (int j = 0; j < 3; j++) {
				  p1(j) = SV(F(i, k), j);
				  p2(j) = SV(F(i, (1 + k) % 4), j);
				  p3(j) = SV(FC(i, 0), j);
				  p4(j) = SV(FC(ff, 0), j);
			  }
			  new_point = calcuate_face_center(p1, p2, p3, p4);

			  ind = SV.rows();
			  SV.conservativeResize(ind + 1, 3);
			  SV(ind, 0) = new_point(0);
			  SV(ind, 1) = new_point(1);
			  SV(ind, 2) = new_point(2);
			  FE(i, k) = ind;
		  }
// std::cout << ".......:" << k << "th edgt of face " << i << "====index: "<<FE(i,k)<<" near:" <<ff<<" :"<< SV(FE(i, k), 0) << " " << SV(FE(i, k), 1) << " " << SV(FE(i, k), 2) << "\n";
	  }
  }

  // re-calculate original poinsts
  for (int i = 0; i < V.rows(); i++) {
	  Eigen::Vector3d FF, RR;
	  FF = Eigen::Vector3d(0, 0, 0);
	  RR = Eigen::Vector3d(0, 0, 0);
	  for (int j = 0; j < VF[i].size(); j++) {
		  int nf = VF[i][j];
		  FF(0) = SV(FC(nf, 0), 0) + FF(0);
		  FF(1) = SV(FC(nf, 0), 1) + FF(1);
		  FF(2) = SV(FC(nf, 0), 2) + FF(2);

		  for (int k = 0; k < F.cols(); k++) {
			  if (F(nf, k) == i) {
				  RR(0) = RR(0) + SV(FE(nf, k), 0) + SV(FE(nf, (k + 3) % 4), 0);
				  RR(1) = RR(1) + SV(FE(nf, k), 1) + SV(FE(nf, (k + 3) % 4), 1);
				  RR(2) = RR(2) + SV(FE(nf, k), 2) + SV(FE(nf, (k + 3) % 4), 2);
				  break;
			  }
		  }
	  }
	  RR = RR / (2*VF[i].size());
	  FF = FF / VF[i].size();
	  SV(i, 0) = (FF(0) + 2 * RR(0) + (VF[i].size() - 3) * SV(i, 0)) / VF[i].size();
	  SV(i, 1) = (FF(1) + 2 * RR(1) + (VF[i].size() - 3) * SV(i, 1)) / VF[i].size();
	  SV(i, 2) = (FF(2) + 2 * RR(2) + (VF[i].size() - 3) * SV(i, 2)) / VF[i].size();
  }
  
  //generate new faces
  for (int i=0; i<F.rows(); i++) {
	  for (int k = 0; k < 4; k++) {
		  SF(i * 4+k, 0) = FE(i, (k+3)%4);
		  SF(i * 4+k, 1) = F(i, k);
		  SF(i * 4+k, 2) = FE(i, k);
		  SF(i * 4+k, 3) = FC(i, 0);
//std::cout << SF(i * 4+k, 0) << " " << SF(i * 4 + k, 1) << " " << SF(i * 4 + k, 2) << " " << SF(i * 4 + k, 3) << "\n";
	  }
	  //std::cout << SV.rows() <<" "<< SF.rows() << "\n";
	  //new_point(0) = (V(F(i, 0)) + V(F(i, 1)) + V(F(i, 2)) + V(F(i, 3)))/ 4;
  } 
}

void catmull_clark(
	const Eigen::MatrixXd & V,
	const Eigen::MatrixXi & F,
	const int num_iters,
	Eigen::MatrixXd & SV,
	Eigen::MatrixXi & SF)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	Eigen::MatrixXd V1;
	Eigen::MatrixXi F1;

	SV = V;
	SF = F;
	for (int iter = 0; iter < num_iters; iter++) {
		//V1.resize(SV.rows(), SV.cols());
		//F1.resize(SF.rows(), SF.cols());
		V1 = SV;
		F1 = SF;

		do_catmull_clark(V1, F1, SV, SF);
	}
	return;
}

