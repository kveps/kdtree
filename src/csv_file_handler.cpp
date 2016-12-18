#include <csv_file_handler.h>	

namespace kdtrees {

template<typename T>
CsvFileHandler<T>::CsvFileHandler(std::string filename)
:
m_filename(filename) {
}

template<typename T>
CsvFileHandler<T>::~CsvFileHandler() {
}

template<typename T>
Points<T> CsvFileHandler<T>::ReadPointsFromFile() {
	std::ifstream file(m_filename.c_str());
	std::vector<std::vector<T>> points_list;
	std::string cell;	
	std::string line;
	Points<T> data;

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

	data.FillPoints(points_list);

	return data;
}

template<typename T>
void CsvFileHandler<T>::WriteTreeToFile(const Node<T>* node) {
	std::ofstream file(m_filename.c_str(), std::ios::out | std::ios::trunc);

	if(node == NULL) {
		return;
	}

	std::queue<const Node<T>*> node_q;
	node_q.push(node);

	while(!node_q.empty()) {
		const Node<T>* temp = node_q.front();
		node_q.pop();

		if(temp != NULL) {
			for(unsigned int ind : temp->point_inds) {
				file << ind << ",";
			}
			file << "\n";
			file << temp->level << "\n";
			file << temp->axis << "\n";
			file << temp->median << "\n";
			node_q.push(temp->left);
			node_q.push(temp->right);
		}
	}

	file.close();

}

template<typename T>
void CsvFileHandler<T>::ReadTreeFromFile(Node<T>* temp) {
	std::ifstream file(m_filename.c_str());
	std::string cell; 
	std::string line;
	unsigned int count = 0;

	while(file) {
		while(std::getline(file, line)) {
			std::stringstream line_stream(line);

			switch(count % NUM_NODE_ATTRIBUTES){
				
				case 0:
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
					break;
				default:
					break;
			}

			count++;
		}
	}

	file.close();

}	

template class CsvFileHandler<float>;
template class CsvFileHandler<double>;
template class CsvFileHandler<int>;

} // kdtrees