#include "ray_intersect_triangle.h"
#include <iostream>

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
  t = 0;

  double xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
  double a, b, c, d, e, f, g, h, i, j, k, l;
  double AA, BB, CC, M, beta, gama;
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
  AA = j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g);
  BB = i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c);
  CC = f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c);
  M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);


  if (M != 0) {
	  beta = AA / M;
	  gama = BB / M;
	  t = -CC / M;
	//  std::cout << "hit time " << t;
  }
  else
	  return false;
  if (t >= min_t && t <= max_t) {
	 return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

