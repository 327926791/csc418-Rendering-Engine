#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d l, v, h, i;
	Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);	
	Eigen::Vector3d kd = objects[hit_id]->material->kd;
	Eigen::Vector3d ks = objects[hit_id]->material->ks;
	Ray shaddowRay;
	double t1, t0;
	int hit_id0;
	Eigen::Vector3d n0;

	double p = objects[hit_id]->material->phong_exponent;
	v = -ray.direction;
	v = v / sqrt(v.dot(v));

	for (int x = 0; x < lights.size(); x++) {
		lights[x]->direction(ray.origin + ray.direction * t, l, t1);
		l = l / sqrt(l.dot(l));
		i = lights[x]->I;
		h = (v + l) / sqrt((v + l).dot(v + l));

		shaddowRay.direction = l;
		shaddowRay.origin = ray.origin + t * ray.direction;

		if (!first_hit(shaddowRay, 0.1, objects, hit_id0, t0, n0)) {

			rgb[0] = rgb[0] + (kd[0] * i[0] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[0] * i[0] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
			rgb[1] = rgb[1] + (kd[1] * i[1] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[1] * i[1] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
			rgb[2] = rgb[2] + (kd[2] * i[2] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[2] * i[2] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));

		}
		else if (t0 > t1){ //not shadow
			rgb[0] = rgb[0] + (kd[0] * i[0] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[0] * i[0] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
			rgb[1] = rgb[1] + (kd[1] * i[1] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[1] * i[1] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
			rgb[2] = rgb[2] + (kd[2] * i[2] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[2] * i[2] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
			//std::cout << "shade: hit" << std::endl;
		}
	}
	

	return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
