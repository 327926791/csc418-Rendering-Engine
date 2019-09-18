#include "cube.h"
#include "sphere.h"
#include "write_obj.h"
#include "QuadViewer.h"
#include "set_texture_from_png.h"
#include <igl/readOBJ.h>
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>


int main(int argc, char * argv[])
{
  /*{
    // Create mesh of a cube
    Eigen::MatrixXd V,UV,NV;
    Eigen::MatrixXi F,UF,NF;
    cube(V,F,UV,UF,NV,NF);
    write_obj("cube.obj",V,F,UV,UF,NV,NF);
    igl::readOBJ("cube.obj",V,UV,NV,F,UF,NF);
    {
      QuadViewer v;
      v.set_mesh(V,F,UV,UF,NV,NF);
      set_texture_from_png("../../shared/data/rubiks-cube.png", v.viewer.data());
      v.launch();
    }
  }

  {
	  // Create mesh of a sphere
	  Eigen::MatrixXd V, UV, NV;
	  Eigen::MatrixXi F, UF, NF;
	  sphere(60, 40, V, F, UV, UF, NV, NF);
	  write_obj("sphere.obj", V, F, UV, UF, NV, NF);
	  igl::readOBJ("sphere.obj", V, UV, NV, F, UF, NF);
	  {
		  QuadViewer v;
		  v.set_mesh(V, F, UV, UF, NV, NF);
		  set_texture_from_png("../../shared/data/earth-square.png", v.viewer.data());
		  v.launch();
	  }
  }*/

	////////

  {
	  Eigen::MatrixXd V, UV, NV;
	  Eigen::MatrixXi F, UF, NF;
	  printf("C:/Users/guyingqi/Desktop/OBJLoaderC++/obj/model/zero.obj");
	  igl::readOBJ("C:/Users/guyingqi/Desktop/OBJLoaderC++/obj/model/blub_triangulated.obj", V, UV, NV, F, UF, NF);
	  {
		  igl::opengl::glfw::Viewer v2;
		  QuadViewer v;
		  printf("set_mesh");
		  v2.data().set_mesh(V, F);
		  //v2.data().set_texture(A, B, C);
		  //v.set_mesh(V, F, UV, UF, NV, NF);
		  printf("launch");
		  //set_texture_from_png("C:/Users/guyingqi/Desktop/Sword_obj/Narsil_UVW_3.png", v.viewer.data());
		  v2.launch();
	  }

  }



}
