#ifndef NEAREST_NBR_KD_TREE_H_
#define NEAREST_NBR_KD_TREE_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <points.h>
#include <node.h>
#include <csv_file_handler.h>

namespace kdtrees {

template<typename T> 
class NearestNbrKdTree {
	public:
		NearestNbrKdTree(const NodePtr<T> root, 
						 const PointsPtr<T> q_pts);
		NearestNbrKdTree(const NodePtr<T> root, 
						 const PointsPtr<T> s_pts,
						 const PointsPtr<T> q_pts);
		
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
		double NEAREST_NBR_DIST;
		unsigned int m_num_s_points;
		unsigned int m_num_q_points;
		unsigned int m_dim_size;

		PointsPtr<T> m_s_points;
		const PointsPtr<T> m_q_points;

		NodePtr<T> m_root;

		std::vector<NodePtr<T>> m_node_vec;
		std::vector<unsigned int> m_best_inds;
		std::vector<T> m_best_dists;
};

} // namespace kdtrees

#endif // NEAREST_NBR_KD_TREE_H_