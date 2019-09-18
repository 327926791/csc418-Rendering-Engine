#include "Sphere.h"
#include "Ray.h"
#include "math.h"
#include "iostream"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double k,t1,t2;
	Eigen::Vector3d d, e, c;
	d = ray.direction;
	e = ray.origin;
	c = center;
	k = (d.dot(e - c)) * (d.dot(e - c)) - d.dot(d) * ((e - c).dot(e - c) - radius * radius);
	//std::cout << "r: " << radius << " k: " << k << std::endl;
	//std::cout << d.dot(e - c) * d.dot(e - c) << "   "<< d.dot(d) << "   " << ((e - c).dot(e - c) - radius*radius) << std::endl;
	if (k < 0) {
		return false;
	}
	else if (k == 0) {
		t = (-d.dot(e - c)) / (d.dot(d));
		if (t >= min_t) {
			n = (e + t*d - c) / radius;
			//std::cout << "k == 0" << std::endl;
			return true;
		}
		else {
			return false;
		}
		
	}
	else if (k > 0) {
		t1 = (-d.dot(e - c) + std::sqrt(k)) / (d.dot(d));
		t2 = (-d.dot(e - c) - std::sqrt(k)) / (d.dot(d));
		t = std::min(t1, t2);
		if (t < min_t) {
			t = std::max(t1, t2);
			if (t < min_t) {
				return false;
			}
			else {
				n = (e + t*d - c)/radius;
				//std::cout << "k > 0, max" << std::endl;
				return true;
			}
		}
		else {
			n = (e + t*d - c) / radius;
			//std::cout << "k > 0, min" << std::endl;
			return true;
		}
	}
		

  ////////////////////////////////////////////////////////////////////////////
}

