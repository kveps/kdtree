#include <nearest_nbr_kd_tree.h>

namespace kdtrees {

template<typename T>
NearestNbrKdTree<T>::NearestNbrKdTree(const Node<T>* root, const Points<T>* pts)
:
m_root(root),
m_s_points(pts) {
	NEAREST_NBR_DIST = 0.5;
}

template<typename T>
NearestNbrKdTree<T>::~NearestNbrKdTree() {
}

template<typename T>
T NearestNbrKdTree<T>::EuclideanDist(const typename Points<T>::Point s_pt,
									 const typename Points<T>::Point q_pt) {
	if(s_pt.cols() != q_pt.cols()) {
		throw std::invalid_argument("Sample and query of different sizes");
	}

	T dist = 0.0;
	for(unsigned int i = 0; i < s_pt.cols(); ++i) {
		dist += (s_pt(0,i) - q_pt(0,i))*(s_pt(0,i) - q_pt(0,i));
	}

	return sqrt(dist);
}

template<typename T>
bool NearestNbrKdTree<T>::NearestDistanceSatisfy(std::vector<unsigned int> 
												 point_inds, const typename 
												 Points<T>::Point pt, 
												 unsigned int& best_ind) {
	T dist;
	T min_dist = 100000.0;
	bool valid_nearest_nbr = false;

	for(unsigned int i : point_inds) {
		dist = EuclideanDist(m_s_points->GetPoint(i), pt);
		if(dist < min_dist) {
			min_dist = dist;
			best_ind = i;
			if(dist < NEAREST_NBR_DIST) {
				valid_nearest_nbr = true;
			}
		}
	}

	return valid_nearest_nbr;
}

template<typename T>
bool NearestNbrKdTree<T>::FindNearestPointInTree(Node<T>* node, const typename 
												 Points<T>::Point pt,
								                 unsigned int& best_ind) {
	if(node->left == NULL) {
		if(NearestDistanceSatisfy(node->point_inds, pt, best_ind)) {
			return true;
		}
		return false;
	}

	if(pt(1,node->axis) <= node->median) {
		if(!FindNearestPointInTree(node->left, pt, best_ind)) {
			return FindNearestPointInTree(node->right, pt, best_ind);
		}
		else {
			return true;
		}
	}
	else {
		if(!FindNearestPointInTree(node->right, pt, best_ind)) {
			return FindNearestPointInTree(node->left, pt, best_ind);
		}
		else {
			return true;
		}
	}
}


} // namespace kdtrees
