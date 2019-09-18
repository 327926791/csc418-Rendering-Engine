#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

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
  sqrd = 0;
  sqrd = 0;

  std::vector<std::shared_ptr<AABBTree>> obj;
  double dis;
  std::shared_ptr<AABBTree> p, q;
  std::priority_queue<double> diss;


  p = root;

  obj.insert(obj.begin(), p);

  while (obj.size() > 0) {
	  p = obj[obj.size() - 1];
	  obj.pop_back();
	  if (p->num_leaves >2) {
		   obj.insert(obj.begin(), std::static_pointer_cast<AABBTree>(p->left));
 		   obj.insert(obj.begin(), std::static_pointer_cast<AABBTree>(p->right));
	  }
	  else if (p->num_leaves == 1) {
		  sqrd = point_box_squared_distance(query, p->box);
		  diss.push(sqrd);
		  if (diss.top() == sqrd)
			  descendant = p->left;
	  }
	  else if (p->num_leaves == 2) {
		  sqrd = point_box_squared_distance(query, p->left->box);
		  diss.push(sqrd);
		  if (diss.top() == sqrd)
			  descendant = p->left;
		  sqrd = point_box_squared_distance(query, p->right->box);
		  diss.push(sqrd);
		  if (diss.top() == sqrd)
			  descendant = p->right;
	  }
  }

  //calculate the projection
  return true;


  return false;
  ////////////////////////////////////////////////////////////////////////////
}
