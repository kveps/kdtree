#ifndef BUILD_KD_TREE_H_
#define BUILD_KD_TREE_H_

// standard includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

// project includes
#include <points.h>
#include <csv_file_handler.h>
#include <node.h>
#include <params.h>
#include <constants.h>

namespace kdtrees {

// \brief Represents methods required
// for kd-tree construction from 
// sample points
template<typename T> 
class BuildKdTree {
	public:

		BuildKdTree() {}
		BuildKdTree(NodePtr<T> root, const PointsPtr<T> s_pts,
			        Params params);
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

		// Number of sample points
		// and dimension of each point
		unsigned int m_dim_size;
		unsigned int m_num_points;

		// Sample points
		const PointsPtr<T> m_s_points;

		// Root of the kd-tree
		NodePtr<T> m_root;

		// Params object
		Params m_params;
};

} // namespace kdtrees

#endif // BUILD_KD_TREE_H_