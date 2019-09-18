#include "viewing_ray.h"
#include <Eigen/Core>
#include <iostream>

void viewing_ray(
        const Camera & camera,
        const int i,
        const int j,
        const int width,
        const int height,
        Ray & ray) {
    ////////////////////////////////////////////////////////////////////////////
    // Add your code here
    double u, v;
	//std::cout << "i: " << i << " j: " << j << std::endl;
    ray.origin = camera.e;
    u = -camera.width / 2 + camera.width * (j + 0.5) / width; 
    v = camera.height / 2 - camera.height * (i + 0.5) / height; 
	ray.direction = Eigen::Vector3d(u*camera.u + v*camera.v - camera.d*camera.w);
	
	//std::cout << "u: " << u << " v: " << v << std::endl;
    return;
    ////////////////////////////////////////////////////////////////////////////
}

