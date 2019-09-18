#include "first_hit.h"
#include "iostream"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:	
	t = -1;
	hit_id = -1;
	for (int i = 0; i < objects.size(); i++) {
		Eigen::Vector3d normal;
		double t1;
		if (objects[i]->intersect(ray, min_t, t1, normal) == true) {
			//std::cout << "hit" << std::endl;
			if (t == -1) {
				t = t1;
				hit_id = i;
				n = normal;
			}
			else if (t1 < t) {
				t = t1;
				n = normal;
				hit_id = i;
			}
		}
	}
	
	if (t == -1) {
		hit_id = 0;
		return false;
	}
	else {
		//std::cout << "hit_id: " << hit_id << std::endl;
		return true;
	}
		
  ////////////////////////////////////////////////////////////////////////////
}
