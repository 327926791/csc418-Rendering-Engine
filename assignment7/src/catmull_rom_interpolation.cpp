#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
#include <algorithm> // std::max
#include <iostream>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	double keytime, h00, h01, h10, h11;
    Eigen::Vector3d p0, p1, p2, p3, m0, m1, m2, m3, m4;
	double tt, t0, t1, t2, t3;
	int i;

	//std::cout << "..............catmull_rom "<< keyframes.size()<<"  "<<t<<"\n";
	if (keyframes.size() == 0)
		return Eigen::Vector3d(0, 0, 0);

	if (keyframes.size() == 1)
		return keyframes[0].second;

	t = std::fmod(t, keyframes.back().first);

	int index = 0;
	while (t > keyframes[index].first) {
			index += 1;
	}

	if (index-2<0 || index == keyframes.size() -1) {
		t = (keyframes[index].first - t) / (keyframes[index].first - keyframes[index-1].first);
		return (t * keyframes[index-1].second + (1 - t)*keyframes[index].second);
	}

	keytime = keyframes[index].first;
	double k00, k01, k10, k11, k20, k21, k30, k31, k40, k41;

		p0 = keyframes[index-2].second;
		p1 = keyframes[index-1].second;
		p2 = keyframes[index].second;
		p3 = keyframes[index+1].second;

		t0 = keyframes[index-2].first;
		t1 = keyframes[index-1].first;
		t2 = keyframes[index].first;
		t3 = keyframes[index+1].first;

		t3 -= t0;
		t2 -= t0;
		t1 -= t0;
		t -= t0;
		t0 = 0;

		std::cout << "p0,01,m0,m1:" << p0 << " " << p1 << "\n";

		k00 = (t1 - t) / (t1 - t0);
		k01 = (t - t0) / (t1 - t0);
		k10 = (t2 - t) / (t2 - t1);
		k11 = (t - t1) / (t2 - t1);

		k20 = (t3 - t) / (t3 - t2);
		k21 = (t - t2) / (t3 - t2);

		k30 = (t2 - t) / (t2 - t0);
		k31 = (t - t0) / (t2 - t0);

		k40 = (t3 - t) / (t3 - t1);
		k41 = (t - t1) / (t3 - t1);

		m0 = k00 * p0 + k01 * p1;
		m1 = k10 * p1 + k11 * p2;
		m2 = k20 * p2 + k21 * p3;

		m3 = k30 * m0 + k31 * m1;
		m4 = k40 * m1 + k41 * m2;

	
	p0 = keyframes[index-2].second;
	p1 = keyframes[index-1].second;
	p2 = keyframes[index].second;
	p3 = keyframes[index+1].second;
	t0 = keyframes[index-2].first;
	t1 = keyframes[index-1].first;
	t2 = keyframes[index].first;
	t3 = keyframes[index + 1].first;

	m0 = (p2 - p0)/(t2 - t0);
	m1 = (p3 - p1)/(t3 - t1);

	tt = (t - t1) / (t2 - t1);
	h00 = 2 * pow(tt, 3) - 3 * pow(tt, 2) + 1;
	h01 = -2 * pow(tt, 3) + 3 * pow(tt, 2);
	h10 = pow(tt, 3) - 2 * pow(tt, 2) + tt;
	h11 = pow(tt, 3) - pow(tt, 2);
	//Eigen::Vector3d new_xzx = h00 * p1 + h10 * m0 + h01 * p2 + h11 * m1;
	

	
	Eigen::Vector3d new_xzx = k10 *m3 + k11 * m4;
	std::cout <<"after catmull:"<< new_xzx<<"\n";
	return new_xzx ;

  /////////////////////////////////////////////////////////////////////////////
}
