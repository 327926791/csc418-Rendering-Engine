#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>


bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream myfile;

  myfile.open(filename);

  myfile << "# List of geometric vertices, with(x, y, z[, w]) coordinates, w is optional and defaults to 1.0.\n";
  for (int i = 0; i < V.rows(); i++) {
	  myfile << "v ";
	  for (int j = 0; j < V.cols(); j++) {
		  myfile<< V(i,j) << " ";
	  }
	  myfile << "\n";
  }

  myfile << "# List of texture coordinates, in (v, v [,w]) coordinates, these will vary between 0 and 1, w is optional and defaults to 0.\n";
  for (int i = 0; i < UV.rows(); i++) {
	  myfile << "vt " << UV(i, 0) << " " << UV(i, 1) << "\n";
  }

  myfile << "# List of vertex normals in(x, y, z) form; normals might not be unit vectors.\n";
  for (int i = 0; i < NV.rows(); i++) {
	  myfile << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << "\n";
  }

  myfile << "# Polygonal face element (see below).\n";
  for (int i = 0; i < F.rows(); i++) {
	  myfile << "f ";
	  for (int j = 0; j < F.cols(); j++) {
		  myfile << F(i, j) << "/" << UF(i, j) << "/" << NF(i, j) << " ";
	  }
	  myfile << "\n";
  }
  
  myfile.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
  return false;
}
