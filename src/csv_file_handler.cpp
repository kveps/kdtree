#include <csv_file_handler.h>	

namespace kdtrees {

// \brief Constructing based on filename
template<typename T>
CsvFileHandler<T>::CsvFileHandler(std::string filename)
:
m_filename(filename) {
}

// \brief Destroymember variables
template<typename T>
CsvFileHandler<T>::~CsvFileHandler() {
}

// \brief Update filename
template<typename T>
void CsvFileHandler<T>::UpdateFileName(std::string filename) {
	m_filename = filename;
}

// \brief Reads sample and query points
template<typename T>
void CsvFileHandler<T>::ReadPointsFromFile(PointsPtr<T> points) {
	std::ifstream file(m_filename.c_str());
	std::vector<std::vector<T>> points_list;
	std::string cell;	
	std::string line;

	while(file) {
		while(std::getline(file, line)) {
			std::stringstream line_stream(line);
			std::vector<T> point;
			while(std::getline(line_stream, cell, ',')) {
				point.push_back(atof(cell.c_str()));
			}

			points_list.push_back(point);
		}
	}

	file.close();

	points->FillPoints(points_list);
}

// \brief writes kd-tree to file
template<typename T>
void CsvFileHandler<T>::WriteTreeToFile(NodePtr<T> node, 
										const PointsPtr<T> points) {
	std::ofstream file(m_filename.c_str(), std::ios::out | std::ios::trunc);

	if(node == NULL) {
		return;
	}

	std::queue<NodePtr<T>> node_q;
	node_q.push(node);
	file << points->GetPointsSize() << std::endl;
	for(unsigned int i = 0 ; i < points->GetPointsSize(); ++i) {
		for(unsigned int j = 0; j < points->GetPointDim(); ++j) {
			file << points->GetPointValAtIndex(i,j) << ",";
		}
		file << std::endl;
	}
	while(!node_q.empty()) {
		NodePtr<T> temp = node_q.front();
		node_q.pop();

		if(temp != NULL) {
			for(unsigned int ind : temp->point_inds) {
				file << ind << ",";
			}
			file << std::endl;
			file << temp->level << std::endl;
			file << temp->axis << std::endl;
			file << temp->median << std::endl;
			node_q.push(temp->left);
			node_q.push(temp->right);
		}
	}

	file.close();
}

// \brief Read tree from file for nearest
// neighbour search
template<typename T>
void CsvFileHandler<T>::ReadTreeFromFile(std::vector<NodePtr<T>>& node_vec,
										 PointsPtr<T> points) {
	std::ifstream file(m_filename.c_str());
	std::string cell; 
	std::string line;
	unsigned int num_points;
	std::vector<std::vector<T>> points_list;
	unsigned int count = 0;
	bool fill_sample_points = false;

	NodePtr<T> temp;

	while(file) {
		while(std::getline(file, line)) {
			std::stringstream line_stream(line);

			if(!fill_sample_points) {
				if(count == 0) {
					while(std::getline(line_stream, cell, ',')) {
						num_points = atoi(cell.c_str());
					}
				}
				else {
					std::vector<T> point;
					while(std::getline(line_stream, cell, ',')) {
						point.push_back(atof(cell.c_str()));
					}	
					points_list.push_back(point);
				}
				if(count == num_points) {
					fill_sample_points = true;
					count = -1;
					points->FillPoints(points_list);
				}
			}
			else {
				switch(count % NumNodeAttributes) {
					
					case 0:
						temp.reset(new Node<T>);
						temp->left = NULL;
						temp->right = NULL;
						while(std::getline(line_stream, cell, ',')) {
							(temp->point_inds).push_back(atoi(cell.c_str()));
						}
						break;
					case 1:
						while(std::getline(line_stream, cell, ',')) {
							temp->level = atoi(cell.c_str());
						}
						break;
					case 2:
						while(std::getline(line_stream, cell, ',')) {
							temp->axis = atoi(cell.c_str());
						}
						break;
					case 3:
						while(std::getline(line_stream, cell, ',')) {
							temp->median = atof(cell.c_str());
						}
						node_vec.push_back(temp);
						break;
					default:
						break;
				}
			}

			count++;
		}
	}

	file.close();
}	

// \brief Write results of the nearest
// neighbour to a file
template<typename T>
void CsvFileHandler<T>::WriteNNSearchToFile(const std::vector<unsigned int>
											best_inds,
											const std::vector<T>
											best_dists) {
	if(best_inds.size() != best_dists.size()) {
		throw std::length_error("Number of indices and dists different");
		exit(1);
	}

	std::ofstream file(m_filename.c_str(), std::ios::out | std::ios::trunc);

	for(unsigned int i = 0; i < best_inds.size(); i++) {
		file << best_inds[i] << ",";
		file << best_dists[i] << std::endl;
	}

	file.close();
}

template class CsvFileHandler<float>;
template class CsvFileHandler<double>;
template class CsvFileHandler<int>;

} // kdtrees