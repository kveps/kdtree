#include <points.h>

namespace kdtrees {

// \brief Empty Points constructor
template<typename T>
Points<T>::Points() {
}

// \brief Copy constructing on input Point object
template<typename T>
Points<T>::Points(const Points<T> &pts) {
	m_data = pts.GetPoints(); 
}

// \brief Constructing on input vector of vectors
template<typename T>
Points<T>::Points(std::vector<std::vector<T>> data) { 
	if(!data.size()) {
		throw std::length_error("Size of point list is zero");
		exit(1);
	}

	if(!data[0].size()) {
		throw std::length_error("Dimension of point is zero");
		exit(1);
	}

	m_data.resize(data.size(),data[0].size());

	StoreEigenVector(data);
}

// \brief Destroy member variables
template<typename T>
Points<T>::~Points() {
	m_data.resize(0,0);
}

// \brief Fill member variable based on input vector of vectors
template<typename T>
void Points<T>::FillPoints(std::vector<std::vector<T>> data) { 
	if(!data.size()) {
		throw std::length_error("Size of point list is zero");
		exit(1);
	}

	if(!data[0].size()) {
		throw std::length_error("Dimension of point is zero");
		exit(1);
	}

	m_data.resize(data.size(),data[0].size());

	StoreEigenVector(data);
}

// \brief Convert vector of vectors to Eigen Matrix
template<typename T>
void Points<T>::StoreEigenVector(std::vector<std::vector<T>> data) { 

	for(unsigned int i = 0; i < data.size(); ++i) {
		for(unsigned int j = 0; j < data[0].size(); ++j) {
			m_data(i, j) = data[i][j];
		}
	}
}

// \brief Print all points held by the object
template<typename T>
void Points<T>::PrintPoints() const {	
	for(unsigned int i = 0; i < m_data.rows(); ++i) {
		std::cout << "Point " << (i+1) << ": ";
		for(unsigned int j = 0; j < m_data.cols(); ++j) {
			std::cout << m_data(i,j) << " ";
		}
		std::cout << std::endl;
	}
}

// \brief Print point by index
template<typename T>
void Points<T>::PrintPoint(int m) const {	
	if(m >= m_data.rows()) {
		throw std::invalid_argument("Input argument greater than size");
		exit(1);
	}
	std::cout << "Point " << m << ": ";
	for(unsigned int j = 0; j < m_data.cols(); ++j) {
		std::cout << m_data(m,j) << " ";
	}
	std::cout << std::endl;
}

// \brief Get the entire set of points
template<typename T>
typename Points<T>::PointList Points<T>::GetPoints() const {
	return m_data;
}

// \brief Get point by index
template<typename T>
typename Points<T>::Point Points<T>::GetPoint(unsigned int m) const {
	if(m >= m_data.rows()) {
		throw std::invalid_argument("Input argument greater than size");
		exit(1);
	}

	return m_data.row(m);
}

// \brief Get value of a particular point along a dimension
template<typename T>
T Points<T>::GetPointValAtIndex(unsigned int m, unsigned int n) const {
	if(m >= m_data.rows()) {
		throw std::invalid_argument("Input argument greater than size");
		exit(1);
	}

	if(n >= m_data.cols()) {
		throw std::invalid_argument("Input argument greater than size");
		exit(1);
	}

	return m_data(m,n);
}

// \brief Get an entire dimension from entire set of points
template<typename T>
typename Points<T>::PointList Points<T>::GetColumn(unsigned int n) const {
	if(n >= m_data.cols()) {
		throw std::invalid_argument("Input argument greater than size");
		exit(1);
	}

	std::cout << n << std::endl;

	return m_data.col(n);
}

// \brief Get the dimension of a single point
template<typename T>
unsigned int Points<T>::GetPointDim() const {
	return m_data.cols();	
}

// \brief Get the size of list of points
template<typename T>
unsigned int Points<T>::GetPointsSize() const {
	return m_data.rows();	
}

template class Points<float>;
template class Points<double>;
template class Points<int>;

} // namespace kdtrees
