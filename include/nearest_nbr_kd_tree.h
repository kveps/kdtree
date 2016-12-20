#ifndef NEAREST_NBR_KD_TREE_H_
#define NEAREST_NBR_KD_TREE_H_

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

// \brief Represents definitions to do nearest neighbour
// search on a tree(can also be read from a  file)
template<typename T> 
class NearestNbrKdTree {
	public:

		NearestNbrKdTree(const NodePtr<T> root, 
						 const PointsPtr<T> q_pts,
						 Params params);
		NearestNbrKdTree(const NodePtr<T> root, 
						 const PointsPtr<T> s_pts,
						 const PointsPtr<T> q_pts,
						 Params params);
		
		~NearestNbrKdTree();
		T EuclideanDist(const unsigned int s_ind,
						const unsigned int q_ind);
		bool NearestDistanceSatisfy(std::vector<unsigned int> point_inds, 
									const unsigned int q_ind, 
									unsigned int& best_ind,
									T& best_dist);
		bool FindNearestPointInTree();
		bool FindNearestPointInTree(const NodePtr<T> node, 
									const unsigned int q_ind,
								    unsigned int& best_ind,
								    T& best_dist);
		void PrintTree() const;
		void PrintTree(const NodePtr<T> node) const;
		void ReadTreeFromFile(CsvFileHandler<T>* csv_handler);
		void ReconstructTreeFromQueue();
		void WriteNNSearchToFile(CsvFileHandler<T>* csv_handler);

	private:

		// Number of query points
		// and dimension of each point
		unsigned int m_num_points;
		unsigned int m_dim_size;

		// Sample and query point objects
		PointsPtr<T> m_s_points;
		const PointsPtr<T> m_q_points;

		// Root of the kd-tree
		NodePtr<T> m_root;

		// Params object
		Params m_params;

		// Vector to read tree nodes from file
		std::vector<NodePtr<T>> m_node_vec;

		// Best nearest index of each query point 
		// and their corresponding distance 
		std::vector<unsigned int> m_best_inds;
		std::vector<T> m_best_dists;
};

} // namespace kdtrees

#endif // NEAREST_NBR_KD_TREE_H_