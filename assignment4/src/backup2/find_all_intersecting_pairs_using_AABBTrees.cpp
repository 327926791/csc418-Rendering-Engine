#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include "MeshTriangle.h"

// Hint: use a list as a queue
#include <list> 
#include<iostream>
void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
	std::shared_ptr<AABBTree> p, q, pp, qq;
	std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>  inter_pair;

	p = rootA;
	q = rootB;

	//std::cout << p->num_leaves << "  " << q->num_leaves << "\n";
	if (p->num_leaves<=2 && q->num_leaves<= 2) {
		if (p->left != NULL && q->left != NULL) {
			//std::cout << "\ncompare " << p->left->box.min_corner << " " << p->left->box.max_corner << " with \n" << q->left->box.min_corner << q->left->box.max_corner << "\n";
			std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->left);
			std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->left);
			//std::cout << A->f << "  " << B->f;
			if (box_box_intersect(p->left->box, q->left->box)) {
				inter_pair = std::make_pair(p->left, q->left);
				leaf_pairs.push_back(inter_pair);

				//std::cout <<"match \n";
			}
		}
		if (p->left != NULL && q->right != NULL) {
			//std::cout << "\ncompare " << p->left->box.min_corner << " " << p->left->box.max_corner << " with \n" << q->right->box.min_corner << q->right->box.max_corner << "\n";
			std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->left);
			std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->right);
			//std::cout << A->f << "  " << B->f;
			if (box_box_intersect(p->left->box, q->right->box)) {
				inter_pair = std::make_pair(p->left, q->right);
				leaf_pairs.push_back(inter_pair);


				//std::cout << "match \n";
			}
		}
		if (p->right != NULL && q->left != NULL) {
			//std::cout << "\ncompare " << p->right->box.min_corner << " " << p->right->box.max_corner << " with \n" << q->left->box.min_corner << q->left->box.max_corner << "\n";
			std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->right);
			std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->left);
			//std::cout << A->f << "  " << B->f; // << "match \n";
			if (box_box_intersect(p->right->box, q->left->box)) {
				inter_pair = std::make_pair(p->right, q->left);
				leaf_pairs.push_back(inter_pair);

				std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->right);
				std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->left);
				//std::cout <<  "match \n";
			}
		}
		if (p->right != NULL && q->right != NULL) {
			//std::cout << "compare " << p->right->box.min_corner << " " << p->right->box.max_corner << " with \n" << q->right->box.min_corner << q->right->box.max_corner << "\n";
			std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->right);
			std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->right);
			//std::cout << A->f << "  " << B->f ;
			if (box_box_intersect(p->right->box, q->right->box)) {
				inter_pair = std::make_pair(p->right, q->right);
				leaf_pairs.push_back(inter_pair);

				std::shared_ptr<MeshTriangle> A = std::static_pointer_cast<MeshTriangle>(p->right);
				std::shared_ptr<MeshTriangle> B = std::static_pointer_cast<MeshTriangle>(q->right);
				//std::cout <<  "match \n";
			}
		}
		return;
	}


	if (p->num_leaves > 2){
		find_all_intersecting_pairs_using_AABBTrees(std::static_pointer_cast<AABBTree>(p->left), q, leaf_pairs);	
		find_all_intersecting_pairs_using_AABBTrees(std::static_pointer_cast<AABBTree>(p->right), q, leaf_pairs);

	}
	else if (q->num_leaves > 2) {
			find_all_intersecting_pairs_using_AABBTrees(p, std::static_pointer_cast<AABBTree>(q->left), leaf_pairs);
			find_all_intersecting_pairs_using_AABBTrees(p, std::static_pointer_cast<AABBTree>(q->right), leaf_pairs);
	}
	return;

  ////////////////////////////////////////////////////////////////////////////
}
