#include "AABBTree.h"
#include "insert_box_into_box.h"
#include "iostream"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
	int N;
	int AXIS = depth;
	//std::cout << "AXIS:" << AXIS << "\n";
	N = objects.size();
	if (N == 1) {
		left = NULL;
		insert_box_into_box(objects[0]->box, box);
		right = NULL;
		//std::cout << objects[0]->box.min_corner<<" "<<objects[0]->box.max_corner<< "===>\n" << box.min_corner << " " << box.max_corner << "\n";
		//std::cout << "leaf: " <<depth<<"=="<< box.max_corner << box.min_corner << "\n";
	}
	else {
		//sort objects
		BoundingBox temp_obj;

		for (int i = 0; i < objects.size(); i++) {
			for (int j = i + 1; j < objects.size(); j++) {
				if (objects[j]->box.min_corner[AXIS % 3] < objects[i]->box.min_corner[AXIS % 3]) {
					temp_obj = objects[i]->box; // (objects[i]->box.min_corner, objects[i]->box.max_corner);
					objects[i]->box = objects[j]->box;
					objects[j]->box = temp_obj;
				}
			}
		}

		//
		std::vector<std::shared_ptr<Object> > left_obj, right_obj;

		for (int i = 0; i < (N + 1) / 2; i++) {
			insert_box_into_box(objects[i]->box, box);
			left_obj.push_back(objects[i]);
		}
		for (int i = (N + 1) / 2; i < N; i++) {
			insert_box_into_box(objects[i]->box, box);
			right_obj.push_back(objects[i]);
		}

		left = std::static_pointer_cast<Object>(std::make_shared<AABBTree>(left_obj, (AXIS + 1)));

		right = std::static_pointer_cast<Object>(std::make_shared<AABBTree>(right_obj, (AXIS + 1)));
	}
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	t = 0;
	double lt = -1, rt = -1;
	std::shared_ptr<Object> p, q;

	std::cout << "Ray is" << ray.direction << "\n";
	std::cout << "Box is:" << box.max_corner << "|" << box.min_corner << "\n";
	if (ray_intersect_box(ray, box, min_t, max_t, t)) {
		std::cout << " hit high level box ????" << num_leaves << "\n";
		if (num_leaves == 1) {
			descendant = left;
			return true;
		}
		else if (num_leaves == 2) {
			std::cout << "Box is:" << left->box.max_corner << "|" << left->box.min_corner << "\n";
			if (ray_intersect_box(ray, left->box, min_t, max_t, lt)) {
				std::cout << "hit left leave!!!\n";
				t = lt;
				descendant = left;
			}
			else
				t = -1;

			std::cout << "Box is:" << right->box.max_corner << "|" << right->box.min_corner << "\n";
			if (ray_intersect_box(ray, right->box, min_t, max_t, rt)) {
				std::cout << "hit right leave!!!\n";
				if (rt < t)
					t = rt;
				descendant = right;
			}
			else
				t = -1;

			if (t > min_t)
				return true;
			else
				return false;
		}
		else if (num_leaves > 2) {
			p = std::static_pointer_cast<AABBTree>(left);
			std::cout << "go left\n";
			if (p->ray_intersect(ray, min_t, max_t, t, descendant))
				lt = t;

			q = std::static_pointer_cast<AABBTree>(right);
			std::cout << "go right\n";
			if (q->ray_intersect(ray, min_t, max_t, t, descendant))
				rt = t;
		}
	}

	if (rt > min_t || lt > min_t) {
		(rt > lt && lt != -1) ? t = lt : t = rt;
		(lt > rt && rt != 01) ? t = rt : t = lt;
		return true;
	}
	else
		return false;
  ////////////////////////////////////////////////////////////////////////////
}