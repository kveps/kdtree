#ifndef NODE_H_
#define NODE_H_

//system includes
#include <iostream>
#include <vector>
#include <memory>

namespace kdtrees {

// \brief Define the node in the kdtree
template<typename T>
struct Node {
	std::vector<unsigned int> point_inds;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	unsigned int level;
	unsigned int axis;
	T median;
};

// typedef shared pointer on Node
template<typename T>
using NodePtr = std::shared_ptr<Node<T>>; 

namespace utils {

// \brief Print contents of a node 
template<typename T> 
inline void PrintNode(const NodePtr<T> node) {
	std::cout << "Node point indices : ";
	for(unsigned int ind : node->point_inds) {
		std::cout << ind << " ";
	}
	std::cout << std::endl;
	std::cout << "Level: " << node->level << std::endl;
	std::cout << "Axis: " << node->axis << std::endl;
	std::cout << "Median: " << node->median << std::endl;
}

} // namespace utils

} // namespace kdtrees

#endif // NODE_H_