#include "line_search.h"
#include <iostream>

void print_angle(Eigen::VectorXd & a) {
	std::cout << ".................angle.............\n";
	for (int i = 0; i < a.size(); i++)
		std::cout << a.row(i)(0)<<"\n";
};

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	Eigen::VectorXd zz,ddz=dz;
	zz = z;
	double energy0, energy;
	int iter = 0;
	double delta = 10000;

	proj_z(zz);
	energy0 = energy = f(zz);

	while (energy >= energy0 && iter < max_step) {
		delta = delta / 2;
		zz = zz - delta * dz;
		proj_z(zz);
		energy = f(zz);
		iter++;
	}
	return delta;

  /////////////////////////////////////////////////////////////////////////////
}
