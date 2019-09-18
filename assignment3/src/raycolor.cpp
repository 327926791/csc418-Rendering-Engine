#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "iostream"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	bool res;
	Eigen::Vector3d n;
	Eigen::Vector3d reflect_rgb = Eigen::Vector3d(0, 0, 0);
	Ray inRay, reflectRay;
	inRay.direction = ray.direction;
	inRay.origin = inRay.origin;
	int num_recursive_calls0 = num_recursive_calls;
	double min_t0 = 0.1;

	double t,max_t;
	int hit_id;
	if (first_hit(ray, min_t, objects, hit_id, t, n)) {		
		res = true;
		rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
		Eigen::Vector3d km = objects[hit_id]->material->km;

		//如果表面有反射光，km !=  0, 并且反射的次数不超过最大值，最大值可以自己定，比如10次
		if ((km[0] != 0 || km[1] != 0 || km[0] != 0) && num_recursive_calls0 <= 5) {
			//std::cout << "reflect" << std::endl;
				//计算反射光
			reflectRay.direction = reflect(inRay.direction, n);
			reflectRay.origin = ray.origin + ray.direction*t;
			//std::cout << num_recursive_calls0 << std::endl;
					//计算反射光射到物体时产生的颜色
			raycolor(reflectRay, 0.1, objects, lights, num_recursive_calls0 + 1, reflect_rgb);

			//rgb = rgb + km * reflect_rgb;
			rgb[0] = rgb[0] + km[0] * reflect_rgb[0];
			rgb[1] = rgb[1] + km[1] * reflect_rgb[1];
			rgb[2] = rgb[2] + km[2] * reflect_rgb[2];
			
		}
	
	}
	else {
		res = false;
		rgb = Eigen::Vector3d(0, 0, 0);
	}

	/*Eigen::Vector3d l, v, h, i;
	//Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
	Eigen::Vector3d kd = objects[hit_id]->material->kd;
	Eigen::Vector3d ks = objects[hit_id]->material->ks;
	double p = objects[hit_id]->material->phong_exponent;
	v = -ray.direction;
	v = v / sqrt(v.dot(v));

	for (int x = 0; x < lights.size(); x++) {
		lights[x]->direction(ray.direction * t, l, max_t);
		l = l / sqrt(l.dot(l));
		i = lights[x]->I;
		h = (v + l) / sqrt((v + l).dot(v + l));
		//rgb = rgb + (kd.cross3(i) * (n.dot(l) > 0 ? n.dot(l) : 0) + ks.cross3(i) * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));

		rgb[0] = rgb[0] + (kd[0] * i[0] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[0] * i[0] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
		rgb[1] = rgb[1] + (kd[1] * i[1] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[1] * i[1] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
		rgb[2] = rgb[2] + (kd[2] * i[2] * (n.dot(l) > 0 ? n.dot(l) : 0) + ks[2] * i[2] * (n.dot(h) > 0 ? pow(n.dot(h), p) : 0));
	}*/

 // rgb = Eigen::Vector3d(0,0,0);
  return res;
  ////////////////////////////////////////////////////////////////////////////
}
