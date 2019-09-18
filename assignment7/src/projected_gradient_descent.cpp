#include "projected_gradient_descent.h"
#include "line_search.h"
#include <iostream>

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
	//std::cout << ".....project gradient z size:"<<z.size()<<"\n";
	Eigen::VectorXd a ;
	Eigen::VectorXd zz, dz;

	zz = z;
	a = grad_f(zz);
	double delta = line_search(f, proj_z, zz, a, max_iters);
	z = z - delta * a;
	proj_z(z);

  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  /////////////////////////////////////////////////////////////////////////////
}
