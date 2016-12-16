#include <point.h>

namespace kdtrees {

template<typename T>
Point<T>::Point(std::vector<T> data) { 
	if(!data.size()) {
		throw std::invalid_argument("Size of input data is zero");
	}

	StoreEigenVector(data);
}

template<typename T>
Point<T>::~Point() {
	m_data.clear();
}

template<typename T>
void Point<T>::FillPoint(std::vector<T> data) { 
	if(!data.size()) {
		throw std::invalid_argument("Size of input data is zero");
	}

	StoreEigenVector(data);
}

template<typename T>
Point<T>::StoreEigenVector(std::vector<T> data) { 
	if(!data.size()) {
		throw std::invalid_argument("Size of input data is zero");
	}

	for(unsigned int i = 0; i < data.size(); i++) {
		m_data[i] = data[i];
	}
}

template<typename T>
void Point<T>::PrintPoint() {
	for(int i = 0; i < m_data.size(); ++i)
		std::cout << "Val " << i << " : " << m_data[i] << std::endl;
}

template<typename T>
Eigen::Vector<T> Point<T>::GetPoint() {
	return m_data;
}

template<typename T>
T Point<T>::GetPoint(int n) {
	if(n >= m_data.size()) {
		throw std::invalid_argument("Input argument greater than size");
	}

	return m_data[n-1];
}

template<typename T>
size_t Point<T>::GetPointDim() {
	return m_data.size();	
}

template class Point<float>;
template class Point<double>;
template class Point<int>;

} // namespace kdtrees
