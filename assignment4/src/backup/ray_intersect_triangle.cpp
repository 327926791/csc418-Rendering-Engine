#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
	double a, b, c, d, e, f, g, h, i, j, k, l;
	double X, Y, Z, M, beta, gama;
	xa = A[0];
	xb = B[0];
	xc = C[0];
	xd = ray.direction[0];
	xe = ray.origin[0];
	ya = A[1];
	yb = B[1];
	yc = C[1];
	yd = ray.direction[1];
	ye = ray.origin[1];
	za = A[2];
	zb = B[2];
	zc = C[2];
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

	X = j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g);
	Y = i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c);
	Z = f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c);
	M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

	beta = X / M;
	gama = Y / M;
	t = -Z / M;

	//std::cout << "t: " << t << " beta: " << beta << " gama: " << gama << std::endl;

	if (t >= min_t && t <= max_t) {
		if (gama >= 0 && gama <= 1) {
			if (beta >= 0 && beta <= (1 - gama)) {
				//double n1, n2, n3, nn;
				//n1 = ya * zb + yb * zc + yc * za - ya * zc - yb * za - yc * zb;
				//n2 = -(xa * zb + xb * zc + xc * za - xc * zb - xb * za - xa * zc);
				//n3 = xa * yb + xb * yc + xc * ya - xa * yc - xb * ya - xc * yb;
				//nn = std::sqrt(n1 * n1 + n2 * n2 + n3 * n3);
				//n[0] = n1 / nn;
				//n[1] = n2 / nn;
				//n[2] = n3 / nn;
				return true;
			}
		}
	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

