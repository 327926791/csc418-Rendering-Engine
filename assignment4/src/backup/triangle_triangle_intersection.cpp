#include "triangle_triangle_intersection.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double ax_min, ay_min, az_min, ax_max, ay_max, az_max, bx_min, by_min, bz_min, bx_max, by_max, bz_max;

	//std::cout << A0 << "| " << A1 << "|" << A2 << "    " << B0 << "|" << B1 << "|" << B2 << "\n";

	ax_min = A0(0) < A1(0) ? A0(0) : A1(0);
	ax_min = ax_min < A2(0) ? ax_min : A2(0);

	ay_min = A0(1);
	if (A1(1) < ay_min)
		ay_min = A1(1);
	if (A2(1) < ay_min)
		ay_min = A2(1);

	az_min = A0(2);
	if (A1(2) < az_min)
		az_min = A1(2);
	if (A2(2) < az_min)
		az_min = A2(2);

	ax_max = A0(0) > A1(0) ? A0(0) : A1(0);
	ax_max = ax_max > A2(0) ? ax_max : A2(0);

	ay_max = A0(1) > A1(1) ? A0(1) : A1(1);
	ay_max = ay_max > A2(1) ? ay_max : A2(1);

	az_max = A0(2) > A1(2) ? A0(2) : A1(2);
	az_max = az_max > A2(2) ? az_max : A2(2);


	bx_max = B0(0) > B1(0) ? B0(0) : B1(0);
	bx_max = bx_max > B2(0) ? bx_max : B2(0);

	by_max = B0(1) > B1(1) ? B0(1) : B1(1);
	by_max = by_max > B2(1) ? by_max : B2(1);

	bz_max = B0(2) > B1(2) ? B0(2) : B1(2);
	bz_max = bz_max > B2(2) ? bz_max : B2(2);


	bx_min = B0(0) < B1(0) ? B0(0) : B1(0);
	bx_min = bx_min < B2(0) ? bx_min : B2(0);

	by_min = B0(1) < B1(1) ? B0(1) : B1(1);
	by_min = by_min < B2(1) ? by_min : B2(1);

	bz_min = B0(2) < B1(2) ? B0(2) : B1(2);
	bz_min = bz_min < B2(2) ? bz_min : B2(2);

	if (ax_min > bx_max || bx_min > ax_max || ay_min > by_max || by_min > ay_max || az_min > bz_max || bz_min > az_max)
		return false;
	else {
		//std::cout << "match\n";
		return true;
	}
  ////////////////////////////////////////////////////////////////////////////
}
