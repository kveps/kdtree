#ifndef BUILD_KD_TREE_H_
#define BUILD_KD_TREE_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <points.h>
#include <node.h>
#include <csv_file_handler.h>

namespace kdtrees {

template<typename T> 
class BuildKdTree {
	public:
		BuildKdTree() {}
		BuildKdTree(const Points<T>* pts);
		~BuildKdTree();
		void InitTreeData();
		void RecursivelyBuildTree(Node<T>* node);
		T GetMedianAlongAxis(const Node<T>* node, const unsigned int axis) const;
		void PrintTree() const;
		void PrintTree(const Node<T>* node) const;
		void WriteTreeToFile() const;

	private:
		static const int MAX_POINTS_PER_BIN = 5;

		int m_dim_size;
		int m_num_points;

		const Points<T>* m_points;

		Node<T>* m_root;
};

} // namespace kdtrees

#endif // BUILD_KD_TREE_H_