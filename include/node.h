#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

namespace kdtrees {

template<typename T>
struct Node {
	std::vector<unsigned int> point_inds;
	Node* left;
	Node* right;
	unsigned int level;
	unsigned int axis;
	T median;
};

template<typename T> 
void PrintNode(const Node<T>* node) {
	std::cout << "Node point indices : ";
	for(unsigned int ind : node->point_inds) {
		std::cout << ind << " ";
	}
	std::cout << std::endl;
	std::cout << "Level: " << node->level << std::endl;
	std::cout << "Axis: " << node->axis << std::endl;
	std::cout << "Median: " << node->median << std::endl;
}

}// namespace kdtrees

#endif // NODE_H_