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
		NearestNbrKdTree(const Node<T>* root, const Points<T>* pts);
		~NearestNbrKdTree();
		T EuclideanDist(const typename Points<T>::Point s_pt,
						const typename Points<T>::Point q_pt);
		bool NearestDistanceSatisfy(std::vector<unsigned int> point_inds, 
									const typename Points<T>::Point pt, 
									unsigned int& best_ind);
		bool FindNearestPointInTree(Node<T>* node, const typename 
									Points<T>::Point pt,
								    unsigned int& best_ind);
		void PrintTree() const;
		void PrintTree(const Node<T>* node) const;
		void ReadTreeFromFile() const;

	private:
		static const double NEAREST_NBR_DIST;

		const Points<T>* m_s_points;

		const Node<T>* m_root;
};

} // namespace kdtrees

#endif // NEAREST_NBR_KD_TREE_H_