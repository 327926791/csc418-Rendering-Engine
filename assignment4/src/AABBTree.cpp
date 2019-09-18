#include "AABBTree.h"
#include "insert_box_into_box.h"
#include "MeshTriangle.h"
#include <queue>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
	int N;   
	int AXIS = depth;
	std::vector < std::shared_ptr<Object> > obj;

	N = objects.size();
	// if only one object, put it on left leaf, right leaf is NULL
	if (N == 1) {
		left = objects[0];
		insert_box_into_box(objects[0]->box, box);
		right = NULL;
	}

	// if there are two objects, put one on left leaf, another on right leaf
	else if (N == 2) {
		left = objects[0];
		right = objects[1];
		insert_box_into_box(objects[0]->box, box);
		insert_box_into_box(objects[1]->box, box);
	}

	// if there are more than 2 objects
	else {  
		//sort objects along AXIS
		// first round, sort objects along x-axis, second sorted objects along y-axis, then y-axis, etc
		for (int i = 0; i < objects.size(); i++) {
			obj.push_back(objects[i]);
			insert_box_into_box(objects[i]->box, box);
		}

		for (int i=0; i<obj.size(); i++){
			for (int j = i + 1; j<obj.size(); j++) {
				if (obj[j]->box.center()[AXIS%3] < obj[i]->box.center()[AXIS%3]) {
					obj[i].swap(obj[j]);
				}
			}
		}
		
        // split the sorted objects into two
		std::vector<std::shared_ptr<Object> > left_obj, right_obj;

		for (int i = 0; i<(N +1)/ 2; i++) {
			left_obj.push_back(obj[i]);
		}
		for (int i = (N +1)/ 2; i < N; i++) {
			right_obj.push_back(obj[i]);
		}

        // recursively build sub-AABBTree 
		left = std::static_pointer_cast<Object>(std::make_shared<AABBTree>(left_obj, (AXIS + 1)));
		right = std::static_pointer_cast<Object>(std::make_shared<AABBTree>(right_obj, (AXIS + 1)));
	} 
  ////////////////////////////////////////////////////////////////////////////
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
	struct compare_time {
		constexpr bool operator()
			(std::pair<double, std::shared_ptr<AABBTree>> &a,
				std::pair<double, std::shared_ptr<AABBTree>> &b) const noexcept
		{
			return a.first > b.first;
		}
	};

	std::priority_queue <std::pair<double, std::shared_ptr<AABBTree>>, std::vector<std::pair<double, std::shared_ptr<AABBTree>>>, compare_time> obj;
	std::shared_ptr<AABBTree> p;
	std::shared_ptr<Object> tmp_d;
	std::pair <double, std::shared_ptr<AABBTree>>  tp, stp;
	double min_hit = 999999;

	// if not hit the high level box, return false
	if (!ray_intersect_box(ray, box, min_t, max_t, t))
		return false;
	// if only 2 nodes
	if (num_leaves == 2) {
		if (left->ray_intersect(ray, min_t, max_t, t,tmp_d)) {
			min_hit = t;
			descendant = left;
		}
		if (right->ray_intersect(ray, min_t, max_t, t, tmp_d)) {
			if (t > min_hit) {
				t = min_hit;
			}
			else {
				descendant = right;
			}
		}
		if (t > min_t)
			return true;
		else
			return false;
	}
	if (num_leaves == 1) {
		if (left->ray_intersect(ray, min_t, max_t, t, descendant)) {
			return true;
		}
		else
			return false;
	}

	// if more than 2 objects, 
	if (num_leaves > 2) {
		// check if hit left branch, then put the into priority queue
		if (ray_intersect_box(ray, left->box, min_t, max_t, t)) {
			stp = std::make_pair(t, std::static_pointer_cast<AABBTree>(left));
			obj.push(stp);
		}
		// check if hit right branch, then put the into priority queue
		if (ray_intersect_box(ray, right->box, min_t, max_t, t)) {
			stp = std::make_pair(t, std::static_pointer_cast<AABBTree>(right));
			obj.push(stp);
		}
	}
	
		

	while (obj.size() > 0) {
	// get the top node from the queue
		tp = obj.top();

		// if the hit time is longer than the shortest hit
		// that means, no shorter hit can be found in following boxes
		if (tp.first > min_hit) {
			t = min_hit;
			return true;
		}
		// remove the node from the queue because we has processed it
		obj.pop();

		// the second element in pair is the AABBTree's pointer
		p = tp.second;

		if (p->num_leaves > 2) {
			// if the sub-AABBTree has more than 2 objects
			// check if thr ray hit left/right branches
			// push left and right branches into priority queue if yes
			if (ray_intersect_box(ray, p->left->box, min_t, max_t, t)) {
				stp = std::make_pair(t, std::static_pointer_cast<AABBTree>(p->left));
				obj.push(stp);
			}
			if (ray_intersect_box(ray, p->right->box, min_t, max_t, t)) {
				stp = std::make_pair(t, std::static_pointer_cast<AABBTree>(p->right));
				obj.push(stp);
			}
		}
		// if get the AABBTree's leaf, check if ray hit the leaf
		// store this value and descendant in min_hit and descendant
		else if (p->num_leaves == 1) {
			if (left->ray_intersect(ray, min_t, max_t, t, tmp_d)) {
				if (t < min_hit) {
					min_hit = t;
					descendant = left;
				}
			}
		}
		else if (p->num_leaves == 2) {
			if  (p->left->ray_intersect(ray, min_t, max_t, t, tmp_d)) {
				if (t < min_hit) {
					min_hit = t;
					descendant = p->left;
				}
			}
			if  (p->right->ray_intersect(ray, min_t, max_t, t, tmp_d)) {
				if (t < min_hit) {
					min_hit = t;
					descendant = p->right;
				}
			}
		}
	}
	if (min_hit != 999999) {
		t = min_hit;
		return true;
	}
	return false;
  ////////////////////////////////////////////////////////////////////////////
}
