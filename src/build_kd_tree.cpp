#include <build_kd_tree.h>

namespace kdtrees {

// \brief Construction method of kd-tree
template<typename T> 
BuildKdTree<T>::BuildKdTree(NodePtr<T> root, 
							const PointsPtr<T> s_pts,
							Params params) 
:
m_root(root),
m_s_points(s_pts),
m_params(params) {
	if(!s_pts->GetPointsSize()) {
		throw std::invalid_argument("Size of points is zero");
		exit(1);
	}

	m_num_points = s_pts->GetPointsSize();
	m_dim_size = s_pts->GetPointDim();

	InitTreeData();
}

// \brief Destoy member variables
template<typename T> 
BuildKdTree<T>::~BuildKdTree() {	
}

// \brief Initialize tree root
template<typename T> 
void BuildKdTree<T>::InitTreeData() {
	
	std::vector<unsigned int> root_point_inds;

	for(unsigned int i = 0; i < m_num_points; ++i) {
		root_point_inds.push_back(i);
	}

	m_root->point_inds = root_point_inds;
	m_root->left = NULL;
	m_root->right = NULL;
	m_root->level = 0;
}

// \brief Primary function call 
// to build kd-tree
template<typename T> 
void BuildKdTree<T>::RecursivelyBuildTree() {
	RecursivelyBuildTree(m_root);
}

// \brief Recursively build kd-tree by 
// choosing axis and position to split
template<typename T> 
void BuildKdTree<T>::RecursivelyBuildTree(NodePtr<T>& node) {

	// Get your axis to split and the position
	const unsigned int axis = GetAxis(node);		
	const T median = GetMedianAlongAxis(node, axis);
	node->axis = axis;
	node->median = median;

	// Return when we hit limit on number of points in node
	if((node->point_inds).size() <= m_params.max_points_per_leaf) {
		return;
	}

	NodePtr<T> left_child(new Node<T>);
	NodePtr<T> right_child(new Node<T>);

	// Store points in left and right based on split-position
	for(unsigned int i = 0; i < (node->point_inds).size(); ++i) {
		unsigned int point_list_index = (node->point_inds)[i];

		if(m_s_points->GetPointValAtIndex(point_list_index, axis) <= median) {
			(left_child->point_inds).push_back(point_list_index);
		}
		else {
			(right_child->point_inds).push_back(point_list_index);
		}
	}

	// Define left and right children
	left_child->left = NULL;
	left_child->right = NULL;
	left_child->level = node->level + 1;

	right_child->left = NULL;
	right_child->right = NULL;
	right_child->level = node->level + 1;

	node->left = left_child;
	node->right = right_child;

	// Recursive call
	RecursivelyBuildTree(left_child);
	RecursivelyBuildTree(right_child);
}

// \brief Get axis of split by cycling
// TODO(Karthik) : Also incorporate variance
// and range based axis selection
template<typename T> 
unsigned int BuildKdTree<T>::GetAxis(const NodePtr<T> node) const {
	return node->level % m_dim_size; 
}  

// \brief Get position of split by median
// TODO(Karthik) : Also incorporate median
// of medians
template<typename T> 
T BuildKdTree<T>::GetMedianAlongAxis(const NodePtr<T> node, 
									 const unsigned int axis) const {
	std::vector<T> axis_values;
	for(unsigned int i = 0; i < (node->point_inds).size(); ++i) {
		unsigned int point_list_index = (node->point_inds)[i];
		axis_values.push_back(m_s_points->GetPointValAtIndex(point_list_index,
														   axis));
	}
	std::sort(axis_values.begin(), axis_values.end());
	return axis_values[axis_values.size()/2];
}

// \brief Print entire tree
template<typename T> 
void BuildKdTree<T>::PrintTree() const {
	PrintTree(m_root);
}

// \brief Stores the tree in a queue
// in order to print level by level
template<typename T> 
void BuildKdTree<T>::PrintTree(NodePtr<T> node) const {
	if(node == NULL) {
		return;
	}

	std::queue<NodePtr<T>> node_q;
	node_q.push(node);

	while(!node_q.empty()) {
		NodePtr<T> temp = node_q.front();
		node_q.pop();

		if(temp != NULL) {
			utils::PrintNode(temp);
			node_q.push(temp->left);
			node_q.push(temp->right);
		}
	}
}

// \brief Write tree to file
template<typename T> 
void BuildKdTree<T>::WriteTreeToFile(CsvFileHandler<T>* csv_handler) const {
	csv_handler->WriteTreeToFile(m_root, m_s_points);
}

template class BuildKdTree<float>;
template class BuildKdTree<double>;
template class BuildKdTree<int>;

} // namespace kdtrees
