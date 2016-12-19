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
		BuildKdTree(NodePtr<T> root, const PointsPtr<T> s_pts);
		~BuildKdTree();
		void InitTreeData();
		void RecursivelyBuildTree();
		void RecursivelyBuildTree(NodePtr<T>& node);
		unsigned int GetAxis(const NodePtr<T> node) const;
		T GetMedianAlongAxis(const NodePtr<T> node, 
							 const unsigned int axis) const;
		void PrintTree() const;
		void PrintTree(NodePtr<T> node) const;
		void WriteTreeToFile(CsvFileHandler<T>* csv_handler) const;

	private:
		static const int MAX_POINTS_PER_BIN = 5;

		int m_dim_size;
		int m_num_points;

		const PointsPtr<T> m_s_points;

		NodePtr<T> m_root;
};

} // namespace kdtrees

#endif // BUILD_KD_TREE_H_