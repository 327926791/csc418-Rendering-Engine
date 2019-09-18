#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
	int num_vertex = (num_faces_u + 1) * (num_faces_v + 1);;
	int num_face = num_faces_u * num_faces_v;
	int num_texture = (num_faces_u + 1)*(num_faces_v + 1);

	V.resize(num_vertex, 3);
	F.resize(num_face, 4);
	UV.resize(num_vertex, 2);
	UF.resize(num_face, 4);
	NV.resize(num_vertex, 3);
	NF.resize(num_face, 4);


	//3D vertex
	int n = 0; //place in matrix of the row
	//bottom
	for (int i = 0; i < num_faces_u + 1; i++)
	{
		V.row(n)[0] = 1;
		V.row(n)[1] = 1;
		V.row(n)[2] = 0;
		n++;
	}

	double PI = 3.14159;
	double  x, y, z, dx, dy, dz;
	double z_angle, current_z_angle, current_r, current_angle, angle_gap;
	for (int i = 1; i < num_faces_v; i++) {
		//transform z axis
		z_angle = PI / num_faces_v;
		current_z_angle = z_angle * i;
		z = 1 - cos(current_z_angle);
		current_r = sqrt(1 - abs(1 - z) * abs(1 - z));

		for (int j = 0; j <= num_faces_u; j++) {
			angle_gap = 2 * PI / num_faces_u;
			current_angle = angle_gap * j;
			dx = current_r * cos(current_angle);
			dy = current_r * sin(current_angle);
			x = dx + 1;
			y = dy + 1;

			V.row(n)[0] = x;
			V.row(n)[1] = y;
			V.row(n)[2] = z;
			n++;
		}
	}

	//top
	for (int i = 0; i < num_faces_u + 1; i++){
		V.row(n)[0] = 1;
		V.row(n)[1] = 1;
		V.row(n)[2] = 2;
		n++;
	}

	//3D to 2D texture vetex
	double u = 1.00 / num_faces_u;
	double v = 1.00 / num_faces_v;
	for (int i = 0; i <= num_faces_v; i++) {
		for (int j = 0; j <= num_faces_u; j++) {
			UV.row(i*(num_faces_u + 1) + j)[0] = j * u;
			UV.row(i*(num_faces_u + 1) + j)[1] = i * v;
		}
	}
	
	//normal vectors for each vertex	
	Eigen::RowVector3d centre = Eigen::RowVector3d(1,1,1);
	for (int i = 0; i < V.rows(); i++) {
		Eigen::RowVector3d current = V.row(i);
		Eigen::RowVector3d normal = current - centre;
		normal = normal.normalized();
		NV.row(i)[0] = normal[0];
		NV.row(i)[1] = normal[1];
		NV.row(i)[2] = normal[2];
	}
	

	//setup face vertex index
	int num_vertex_row = num_faces_u + 1;
	n = 0;
    for (int i = 0; i < num_faces_v; i++) {
			for (int j = 0; j < num_faces_u; j++) {
				int index;
				//left bottom
				index = j + i * num_vertex_row;
				F.row(n)[0] = index + 1;
				NF.row(n)[0] = index + 1;
				UF.row(n)[0] = index + 1;

				//right bottom 
				index = j + (i + 1) * num_vertex_row;
				F.row(n)[1] = index + 1;
				NF.row(n)[1] = index + 1;
				UF.row(n)[1] = index + 1;

				//right top 
				index = (j + 1) + (i + 1) * num_vertex_row;
				F.row(n)[2] = index + 1;
				NF.row(n)[2] = index + 1;
				UF.row(n)[2] = index + 1;

				//left top
				index = (j + 1) + i * num_vertex_row;
				F.row(n)[3] = index + 1;
				NF.row(n)[3] = index + 1;
				UF.row(n)[3] = index + 1;
				n++;
			}
		}

  ////////////////////////////////////////////////////////////////////////////
}
