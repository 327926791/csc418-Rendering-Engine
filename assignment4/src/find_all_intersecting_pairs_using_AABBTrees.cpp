#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include "MeshTriangle.h"

// Hint: use a list as a queue
#include <list> 
#include<iostream>
void find_all_intersecting_pairs_using_AABBTrees(
	const std::shared_ptr<AABBTree> & rootA,
	const std::shared_ptr<AABBTree> & rootB,
	std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > &
	leaf_pairs)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	std::shared_ptr<AABBTree> p, q;
	std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>  inter_pair;

	p = rootA;
	q = rootB;

	// if Tree A has more nodes, find the leaf
	if (p->num_leaves > 2) {
		if (box_box_intersect(p->box, q->box)) {
			find_all_intersecting_pairs_using_AABBTrees(std::static_pointer_cast<AABBTree>(p->left), q, leaf_pairs);
			find_all_intersecting_pairs_using_AABBTrees(std::static_pointer_cast<AABBTree>(p->right), q, leaf_pairs);
		}
	}
	// get Tree A's leaf
	else if (p->num_leaves <= 2 && q->num_leaves > 2) {
		// check if A's leaf intersect with high-level B'box
		// if not, skip to check underlying boxes
		if (box_box_intersect(p->box, q->left->box)) {
			find_all_intersecting_pairs_using_AABBTrees(p, std::static_pointer_cast<AABBTree>(q->left), leaf_pairs);
		}
		if (box_box_intersect(p->box, q->right->box)) {
			find_all_intersecting_pairs_using_AABBTrees(p, std::static_pointer_cast<AABBTree>(q->right), leaf_pairs);
		}
	}
    // get Tree A and B leaves, check if they intersect
	else if (p->num_leaves == 1 && q->num_leaves == 1) {
		inter_pair = std::make_pair(p->left, q->left);
		leaf_pairs.push_back(inter_pair);
	}
	else if (p->num_leaves == 1 && q->num_leaves == 2) {
		if (box_box_intersect(p->box, q->left->box)) {
			inter_pair = std::make_pair(p->left, q->left);
			leaf_pairs.push_back(inter_pair);
		}
		if (box_box_intersect(p->box, q->right->box)) {
			inter_pair = std::make_pair(p->left, q->right);
			leaf_pairs.push_back(inter_pair);
		}
	}
	else if (p->num_leaves == 2 && q->num_leaves == 1) {
		if (box_box_intersect(p->left->box, q->left->box)) {
			inter_pair = std::make_pair(p->left, q->left);
			leaf_pairs.push_back(inter_pair);
		}
		if (box_box_intersect(p->right->box, q->left->box)) {
			inter_pair = std::make_pair(p->right, q->left);
			leaf_pairs.push_back(inter_pair);
		}
	}
	else if (p->num_leaves == 2 && q->num_leaves == 2) {
		if (box_box_intersect(p->left->box, q->left->box)) {
			inter_pair = std::make_pair(p->left, q->left);
			leaf_pairs.push_back(inter_pair);
		}
		if (box_box_intersect(p->left->box, q->right->box)) {
			inter_pair = std::make_pair(p->left, q->right);
			leaf_pairs.push_back(inter_pair);
		}
		if (box_box_intersect(p->right->box, q->left->box)) {
			inter_pair = std::make_pair(p->right, q->left);
			leaf_pairs.push_back(inter_pair);
		}
		if (box_box_intersect(p->right->box, q->right->box)) {
			inter_pair = std::make_pair(p->right, q->right);
			leaf_pairs.push_back(inter_pair);
		}
	}
	return;
  ////////////////////////////////////////////////////////////////////////////
}
