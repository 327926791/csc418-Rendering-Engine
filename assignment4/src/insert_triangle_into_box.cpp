#include "insert_triangle_into_box.h"

#include <iostream>

void insert_triangle_into_box(
	const Eigen::RowVector3d & a,
	const Eigen::RowVector3d & b,
	const Eigen::RowVector3d & c,
	BoundingBox & B)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	
	//std::cout << "insert tri to box:" << a << "| " << b << " |" << c << "\n";
	//std::cout << "before insert, box size " << B.max_corner << "|" << B.min_corner << "\n";

	if (a[0] < B.min_corner[0])
		B.min_corner[0] = a[0];
	if (b[0] < B.min_corner[0])
		B.min_corner[0] = b[0];
	if (c[0]< B.min_corner[0])
		B.min_corner[0] = c[0];

	if (a[1] < B.min_corner[1])
		B.min_corner[1] = a[1];
	if (b[1] < B.min_corner[1])
		B.min_corner[1] = b[1];
	if (c[1] < B.min_corner[1])
		B.min_corner[1] = c[1];

	if (a[2] < B.min_corner[2])
		B.min_corner[2] = a[2];
	if (b[2] < B.min_corner[2])
		B.min_corner[2] = b[2];
	if (c[2] < B.min_corner[2])
		B.min_corner[2] = c[2];

	if (a[0] > B.max_corner[0])
		B.max_corner[0] = a[0];
	if (b[0] > B.max_corner[0])
		B.max_corner[0] = b[0];
	if (c[0] > B.max_corner[0])
		B.max_corner[0] = c[0];

	if (a[1] > B.max_corner[1])
		B.max_corner[1] = a[1];
	if (b[1] > B.max_corner[1])
		B.max_corner[1] = b[1];
	if (c[1] > B.max_corner[1])
		B.max_corner[1] = c[1];

	if (a[2] > B.max_corner[2])
		B.max_corner[2] = a[2];
	if (b[2] > B.max_corner[2])
		B.max_corner[2] = b[2];
	if (c[2] > B.max_corner[2])
		B.max_corner[2] = c[2];

	//std::cout << "=======box after insert: " << B.max_corner << " " << B.min_corner << "\n";

  ////////////////////////////////////////////////////////////////////////////
}


