#include <nearest_nbr_kd_tree.h>

namespace kdtrees {

template<typename T>
NearestNbrKdTree<T>::NearestNbrKdTree(const NodePtr<T> root, 
									  const PointsPtr<T> q_pts)
:
m_root(root),
m_q_points(q_pts) {
	NEAREST_NBR_DIST = 0.1;

	m_num_q_points = q_pts->GetPointsSize();
	m_dim_size = q_pts->GetPointDim();

	m_s_points.reset(new Points<T>());
}

template<typename T>
NearestNbrKdTree<T>::NearestNbrKdTree(const NodePtr<T> root, 
									  const PointsPtr<T> s_pts,
									  const PointsPtr<T> q_pts)
:
m_root(root),
m_s_points(s_pts),
m_q_points(q_pts) {
	NEAREST_NBR_DIST = 0.1;

	if(s_pts->GetPointDim() != q_pts->GetPointDim()) {
		throw std::length_error("Sample and query of different dimension");
		exit(1);
	}

	m_num_q_points = q_pts->GetPointsSize();
	m_dim_size = q_pts->GetPointDim();
}

template<typename T>
NearestNbrKdTree<T>::~NearestNbrKdTree() {
}

template<typename T>
T NearestNbrKdTree<T>::EuclideanDist(const unsigned int s_ind,
									 const unsigned int q_ind) {
	T dist = 0.0;
	for(unsigned int i = 0; i < m_dim_size; ++i) {
		dist += (m_s_points->GetPointValAtIndex(s_ind, i) - 
				 m_q_points->GetPointValAtIndex(q_ind, i)) *
				(m_s_points->GetPointValAtIndex(s_ind, i) - 
				 m_q_points->GetPointValAtIndex(q_ind, i));
	}

	return sqrt(dist);
}

template<typename T>
bool NearestNbrKdTree<T>::NearestDistanceSatisfy(std::vector<unsigned int> 
												 point_inds, 
												 const unsigned int q_ind, 
												 unsigned int& best_ind,
												 T& best_dist) {
	T dist;
	T min_dist = 1000000.0;
	bool valid_nearest_nbr = false;

	for(unsigned int i : point_inds) {
		dist = EuclideanDist(i, q_ind);
		if(dist < min_dist) {
			min_dist = dist;
			best_ind = i;
			if(dist < NEAREST_NBR_DIST) {
				valid_nearest_nbr = true;
			}
		}
	}

	best_dist = min_dist;
	return valid_nearest_nbr;
}

template<typename T>
bool NearestNbrKdTree<T>::FindNearestPointInTree() {
	unsigned int index;
	T dist; 

	for(unsigned int i = 0; i < m_num_q_points; i++) {
		FindNearestPointInTree(m_root, i, index, dist);
		m_best_inds.push_back(index);
		m_best_dists.push_back(dist);
	}
}

template<typename T>
bool NearestNbrKdTree<T>::FindNearestPointInTree(const NodePtr<T> node, 
												 unsigned int q_ind,
								                 unsigned int& best_ind,
								                 T& best_dist) {
	if(node->left == NULL) {
		if(NearestDistanceSatisfy(node->point_inds, q_ind,
								  best_ind, best_dist)) {
			return true;
		}
		return false;
	}

	if(m_q_points->GetPointValAtIndex(q_ind,node->axis) <= node->median) {
		if(!FindNearestPointInTree(node->left, q_ind,
								   best_ind, best_dist)) {
			return FindNearestPointInTree(node->right, q_ind,
										  best_ind, best_dist);
		}
		else {
			return true;
		}
	}
	else {
		if(!FindNearestPointInTree(node->right, q_ind,
								   best_ind, best_dist)) {
			return FindNearestPointInTree(node->left, q_ind,
										  best_ind, best_dist);
		}
		else {
			return true;
		}
	}
}

template<typename T> 
void NearestNbrKdTree<T>::PrintTree() const {
	PrintTree(m_root);
}

template<typename T> 
void NearestNbrKdTree<T>::PrintTree(NodePtr<T> node) const {
	if(node == NULL) {
		return;
	}

	std::queue<NodePtr<T>> node_q;
	node_q.push(node);

	while(!node_q.empty()) {
		NodePtr<T> temp = node_q.front();
		node_q.pop();

		if(temp != NULL) {
			PrintNode(temp);
			node_q.push(temp->left);
			node_q.push(temp->right);
		}
	}
}

template<typename T>
void NearestNbrKdTree<T>::ReadTreeFromFile(CsvFileHandler<T>* csv_handler) {
	csv_handler->ReadTreeFromFile(m_node_vec, m_s_points);
	ReconstructTreeFromQueue();
}

template<typename T>
void NearestNbrKdTree<T>::ReconstructTreeFromQueue() {
	if(!m_node_vec.size()) {
		throw std::invalid_argument("Vector of nodes is empty");
		exit(1);
	}

	unsigned int count = 1;

	for(unsigned int i = 0; i < m_node_vec.size(); i++) {
		
		if(i+count >= m_node_vec.size()) {
			m_node_vec[i]->left = NULL;
			m_node_vec[i]->right = NULL;
		}
		else {
			m_node_vec[i]->left = m_node_vec[i+count];
			m_node_vec[i]->right = m_node_vec[i+count+1];
		}
		count++;
	}

	m_root = m_node_vec[0];
}

template<typename T>
void NearestNbrKdTree<T>::WriteNNSearchToFile(CsvFileHandler<T>* csv_handler) {
	csv_handler->WriteNNSearchToFile(m_best_inds, m_best_dists);
}

template class NearestNbrKdTree<float>;
template class NearestNbrKdTree<double>;
template class NearestNbrKdTree<int>;

} // namespace kdtrees
