#include "Triangle.h"
#include "Ray.h"
#include "iostream"

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

	double xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
	double a, b, c, d, e, f, g, h, i, j, k, l;
	double A, B, C, M, beta, gama;
	Eigen::Vector3d pa = std::get<0>(corners);
	Eigen::Vector3d pb = std::get<1>(corners);
	Eigen::Vector3d pc = std::get<2>(corners);
	xa = pa[0];
	xb = pb[0];
	xc = pc[0];
	xd = ray.direction[0];
	xe = ray.origin[0];
	ya = pa[1];
	yb = pb[1];
	yc = pc[1];
	yd = ray.direction[1];
	ye = ray.origin[1];
	za = pa[2];
	zb = pb[2];
	zc = pc[2];
	zd = ray.direction[2];
	ze = ray.origin[2];

	a = xa - xb;
	b = ya - yb;
	c = za - zb;
	d = xa - xc;
	e = ya - yc;
	f = za - zc;
	g = xd;
	h = yd;
	i = zd;
	j = xa - xe;
	k = ya - ye;
	l = za - ze;

	A = j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g);
	B = i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c);
	C = f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c);
	M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

	beta = A / M;
	gama = B / M;
	t = -C / M;

	//std::cout << "t: " << t << " beta: " << beta << " gama: " << gama << std::endl;

	if (t >= min_t) {
		if (gama >= 0 && gama <= 1) {
			if (beta >= 0 && beta <= (1 - gama)) {
				double n1, n2, n3, nn;
				n1 = ya * zb + yb * zc + yc * za - ya * zc - yb * za - yc * zb;
				n2 = -(xa * zb + xb * zc + xc * za - xc * zb - xb * za - xa * zc);
				n3 = xa * yb + xb * yc + xc * ya - xa * yc - xb * ya - xc * yb;
				nn = std::sqrt(n1 * n1 + n2 * n2 + n3 * n3);
				n[0] = n1 / nn;
				n[1] = n2 / nn;
				n[2] = n3 / nn;
				return true;
			}
		}
	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}


