#include "TriangleSoup.h"
#include "Ray.h"
#include "iostream"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	int hit_id;
	//std::cout << triangles.size() << std::endl;
	//for (int i = 0; i < triangles.size(); i++) {
		if (first_hit(ray,min_t,triangles,hit_id,t,n) == true) {			
			return true;
		}
		else {
			return false;
		}
	//}
  
  ////////////////////////////////////////////////////////////////////////////
}



