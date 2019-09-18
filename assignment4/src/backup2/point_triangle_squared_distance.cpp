#include "point_triangle_squared_distance.h"

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
double x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, l, m, n,t, x, y, z, min_dis;
	int not_in_triangle = 0;

	x0 = query[0];
	y0 = query[1];
	z0 = query[2];
	x1 = A[0];
	y1 = A[1];
	z1 = A[2];
	x2 = B[0];
	y2 = B[1];
	z2 = B[2];
	x3 = C[0];
	y3 = C[1];
	z3 = C[2];

	l = (y2 - y1)*(z3 - z1) - (y3 - y1)*(z2 - z1);
	m = (z2 - z1)*(x3 - x1) - (z3 - z1)*(x2 - x1);
	n = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);

	t = (l * (x1 - x0) + m * (y1 - y0) + n * (z1 - z0))/(l*l + m*m + n*n);

	x = x0 + t * l;
	y = y0 + t * m;
	z = z0 + t * n;

	if (n != 0) {
		// check if Q is in triangle
		if (x*y2 + y*x3 + x2*y3 - x3*y2 - x2*y - x*y3 + x1*y + x3*y1 + x*y3 - x3*y - x*y1 - x1*y3 + x1*y2 + x2*y + x*y1 - x*y2 - x2*y1 - x1*y == abs(n))
			min_dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
		// Q is not in triangle
		else
			not_in_triangle = 1;

	}
	else if (m != 0) {
		if (x*z3 + x3*z2 + x2*z - x3*z - x2*z3 - x*z2 + x1*z3 + x3*z + x*z1 - x3*z1 - x*z3 - x1*z + x1*z + x*z2 + x2*z1 - x*z1 - x2*z - x1*z2 == abs(m))
			min_dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
		else
			not_in_triangle = 1;
	}
	else if (l != 0) {
		if (y2*z3 + y*z2 + y3*z - y2*z - y*z3 - y3*z2 + y*z3 + y1*z + y3*z1 - y*z1 - y1*z3 - y3*z + y2*z + y1*z2 + y*z1 - y2*z1 - y1*z - y*z2 == abs(l))
			min_dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
		else
			not_in_triangle = 1;
	}
	
	double dis1, dis2, dis3, dis, min_x, min_y, min_z;
	if (not_in_triangle) {
	    //calculate the distance from query point to line AB
		t = ((x1 - x0)*(x1 - x2) + (y1 - y0)*(y1 - y2) + (z1 - z0)*(z1 - z2)) / (pow((x1 - x2), 1) + pow((y1 - y2), 2) + pow((z1 - z2), 2));
		    // the intersect point Q is on AB line
		    if (t >= 0 && t <= 1) { 
			    x = x1 + t * (x2 - x1);
			    y = y1 + t * (y2 - y1);
			    z = z1 + t * (z2 - z1);
			    dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
				min_x = x;
				min_y = y;
				min_z = z;
				min_dis = dis;
		    }
			// the intersect point Q is not on AB line
			else {
				// distance from P to A
				dis1 = pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2);
				// distance from P to B
				dis2 = pow((x2 - x0), 2) + pow((y2 - y0), 2) + pow((z2 - z0), 2);
				if (dis1 < dis2) {
					min_dis = dis1;
					min_x = x1;
					min_y = y1;
					min_z = z1;
				}
				else {
					min_dis = dis2;
					min_x = x2;
					min_y = y2;
					min_z = z2;
				}
			}
;
			//calculate the distance from query point to line AC
			t = ((x1 - x0)*(x1 - x3) + (y1 - y0)*(y1 - y3) + (z1 - z0)*(z1 - z3)) / (pow((x1 - x3), 1) + pow((y1 - y3), 2) + pow((z1 - z3), 2));
			// Q is on AC line
			if (t >= 0 && t <= 1) { 
				x = x1 + t * (x3 - x1);
				y = y1 + t * (y3 - y1);
				z = z1 + t * (z3 - z1);
				dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
				if (dis < min_dis) {
					min_dis = dis;
					min_x = x;
					min_y = y;
					min_z = z;
				}
			}
			// Q is not on AC line
			else {
				//distance from P to C
				dis3 = pow((x3 - x0), 2) + pow((y3 - y0), 2) + pow((z3 - z0), 2);
				if (dis3 < min_dis) {
					min_dis = dis3;
					min_x = x3;
					min_y = y3;
					min_z = z3;
				}
			}

			//calculate the distance from query point to line BC
			t = ((x2 - x0)*(x2 - x3) + (y2 - y0)*(y2 - y3) + (z2 - z0)*(z2 - z3)) / (pow((x2 - x3), 1) + pow((y2 - y3), 2) + pow((z2 - z3), 2));
			// Q is on BC line
			if (t >= 0 && t <= 1) { 
				x = x2 + t * (x3 - x2);
				y = y2 + t * (y3 - y2);
				z = z2 + t * (z3 - z2);
				dis = pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2);
				if (dis < min_dis) {
					min_dis = dis;
					min_x = x;
					min_y = y;
					min_z = z;
				}
			}
	}

	//convert 3D coordinate to Bary coordinate
	double s, s1, s2, s3, r, q, p;

	x = min_x;
	y = min_y;
	z = min_z;
	s = (x1*y2 *z3 + x2 * y3 *z1 + x3 * y1 *z2 - x1 * y3 *z2 - x2 * y1*z3 - x3 * y2 *z1) / 2;
	s1 = (x*y2 *z3 + x2 * y3 *z + x3 * y *z2 - x * y3 *z2 - x2 * y*z3 - x3 * y2 *z) / 2;
	s2 = (x1*y *z3 + x * y3 *z1 + x3 * y1 *z - x1 * y3 *z - x * y1*z3 - x3 * y *z1) / 2;
	s3 = (x1*y2 *z + x2 * y *z1 + x * y1 *z2 - x1 * y *z2 - x2 * y1*z - x * y2 *z1) / 2;

	q = s1 / s;
    p = s2 / s;
	r = s3 / s;

	bary(0) = r;
	bary(1) = p;
	bary(2) = q;
	return min_dis;  ////////////////////////////////////////////////////////////////////////////
}
