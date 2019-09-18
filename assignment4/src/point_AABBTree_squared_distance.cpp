#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <iostream>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    Eigen::RowVector3d & projection,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
	struct compare_diss {
		constexpr bool operator()
			(std::pair<double, std::shared_ptr<AABBTree>> &a,
				std::pair<double, std::shared_ptr<AABBTree>> &b) const noexcept
		{
			return a.first > b.first;
		}
  };

  std::priority_queue <std::pair<double, std::shared_ptr<AABBTree>>, std::vector<std::pair<double,std::shared_ptr<AABBTree>>>, compare_diss> obj;
  std::shared_ptr<AABBTree> p;
  std::pair <double, std::shared_ptr<AABBTree>>  tp, stp;
  double min_diss=999999;

  p = root;
  std::shared_ptr<Object> tdes;

  // push the root node into priority queue, with distance 9999999
  tp = std::make_pair(min_diss, p);
  obj.push(tp);

  while (obj.size() > 0) {
      // get the top node from the queue
	  tp = obj.top();

	  // if the distance is longer than the nearest distance 
	  // that means, no shorter distance can be found in following boxes
	  if (tp.first > min_diss)
		  break;
	  
	  // remove the node from the queue because we has processed it
	  obj.pop();

	  // the second element in pair is the AABBTree's pointer
	  p = tp.second;

	  if (p->num_leaves > 2) {
		   // if the sub-AABBTree has more than 2 objects
		   // calculate the distance from the point to the box
		   // push left and right leaves into priority queue
		   sqrd = point_box_squared_distance(query, p->box);
		   stp = std::make_pair(sqrd, std::static_pointer_cast<AABBTree>(p->left));
		   obj.push(stp);
		   stp = std::make_pair(sqrd, std::static_pointer_cast<AABBTree>(p->right));
		   obj.push(stp);
	  }
	  // if get the AABBTree's leaf, calculate the distance
	  // if the distance shorter the min_diss
	  // store this value and descendant in min_diss and descendant
	  else if (p->num_leaves == 1) {
		  p->left->point_squared_distance(query, min_sqrd, max_sqrd, sqrd, projection, tdes); // sqrd=point_box_squared_distance(query, p->left->box);
          if (sqrd < min_diss) {
			  descendant = p->left;
			  min_diss = sqrd;
		  }
	  }
	  else if (p->num_leaves == 2) {
		  double lsqrd, rsqrd;
		  p->left->point_squared_distance(query, min_sqrd, max_sqrd, lsqrd, projection, tdes); //lsqrd = point_box_squared_distance(query, p->left->box);
		  p->right->point_squared_distance(query, min_sqrd, max_sqrd, rsqrd, projection, tdes); // rsqrd = point_box_squared_distance(query, p->right->box);
		  if (lsqrd < min_diss) {
			  min_diss = lsqrd;
			  descendant = p->left;
		  }
		  if (rsqrd < min_diss) {
			  min_diss = rsqrd;
			  descendant = p->right;
		  }
	  }
  }

  //calculate the projection
  double x0 = query(0);
  double y0 = query(1);
  double z0 = query(2);

  projection[0] = (x0 < descendant->box.min_corner[0]) ? descendant->box.min_corner[0] : (x0 > descendant->box.max_corner[0]) ? descendant->box.max_corner[0] : x0;
  projection[1] = (y0 < descendant->box.min_corner[1]) ? descendant->box.min_corner[1] : (y0 > descendant->box.max_corner[1]) ? descendant->box.max_corner[1] : y0;
  projection[2] = (z0 < descendant->box.min_corner[2]) ? descendant->box.min_corner[2] : (z0 > descendant->box.max_corner[2]) ? descendant->box.max_corner[2] : z0;

  sqrd = min_diss;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
