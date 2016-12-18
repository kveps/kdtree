#include <build_kd_tree.h>

namespace kdtrees {

template<typename T> 
BuildKdTree<T>::BuildKdTree(const Points<T>* pts) 
:
m_points(pts) {
	if(!pts->GetPointsSize()) {
		throw std::invalid_argument("Size of points is zero");
		exit(1);
	}

	m_num_points = pts->GetPointsSize();
	m_dim_size = pts->GetPointDim();

	m_root = new Node<T>;

	InitTreeData();
}

template<typename T> 
BuildKdTree<T>::~BuildKdTree() {
	
}

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

	RecursivelyBuildTree(m_root);
}

template<typename T> 
void BuildKdTree<T>::RecursivelyBuildTree(Node<T>* node) {
	const unsigned int axis = node->level % m_dim_size;		
	const T median = GetMedianAlongAxis(node, axis);

	node->axis = axis;
	node->median = median;

	if((node->point_inds).size() <= MAX_POINTS_PER_BIN) {
		return;
	}

	Node<T>* left_child = new Node<T>;
	Node<T>* right_child = new Node<T>;

	for(unsigned int i = 0; i < (node->point_inds).size(); ++i) {
		unsigned int point_list_index = (node->point_inds)[i];

		if(m_points->GetPointValAtIndex(point_list_index, axis) <= median) {
			(left_child->point_inds).push_back(point_list_index);
		}
		else {
			(right_child->point_inds).push_back(point_list_index);
		}
	}

	left_child->left = NULL;
	left_child->right = NULL;
	left_child->level = node->level + 1;

	right_child->left = NULL;
	right_child->right = NULL;
	right_child->level = node->level + 1;

	node->left = left_child;
	node->right = right_child;

	RecursivelyBuildTree(left_child);
	RecursivelyBuildTree(right_child);
}

template<typename T> 
T BuildKdTree<T>::GetMedianAlongAxis(const Node<T>* node, 
									 const unsigned int axis) const {
	std::vector<T> axis_values;
	for(unsigned int i = 0; i < (node->point_inds).size(); ++i) {
		unsigned int point_list_index = (node->point_inds)[i];
		axis_values.push_back(m_points->GetPointValAtIndex(point_list_index,
														   axis));
	}
	std::sort(axis_values.begin(), axis_values.end());
	return axis_values[axis_values.size()/2];
}

template<typename T> 
void BuildKdTree<T>::PrintTree() const {
	PrintTree(m_root);
}

template<typename T> 
void BuildKdTree<T>::PrintTree(const Node<T>* node) const {
	if(node == NULL) {
		return;
	}

	std::queue<const Node<T>*> node_q;
	node_q.push(node);

	while(!node_q.empty()) {
		const Node<T>* temp = node_q.front();
		node_q.pop();

		if(temp != NULL) {
			PrintNode(temp);
			node_q.push(temp->left);
			node_q.push(temp->right);
		}
	}
}

template<typename T> 
void BuildKdTree<T>::WriteTreeToFile() const {
	CsvFileHandler<T> csv_writer("/home/karthik/kdtree/data/tree.csv");
	csv_writer.WriteTreeToFile(m_root);
}

template class BuildKdTree<float>;
template class BuildKdTree<double>;
template class BuildKdTree<int>;

} // namespace kdtrees
