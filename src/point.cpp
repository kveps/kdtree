#include <point.h>

namespace kdtrees {

template<typename T>
Point<T>::Point(std::vector<T> data) { 
	if(!data.size()) {
		throw std::invalid_argument("Size of input data is zero");
	}

	m_data = data;
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

	m_data = data;
}

template<typename T>
void Point<T>::PrintPoint() {
	for(int i = 0; i < m_data.size(); ++i)
		std::cout << "Val " << i << " : " << m_data[i] << std::endl;
}

template<typename T>
std::vector<T> Point<T>::GetPoint() {
	return m_data;
}

template<typename T>
T Point<T>::GetPoint(int n) {
	if(n >= m_data.size()) {
		throw std::invalid_argument("Input argument greater than size");
	}

	return m_data[n-1];
}

template class Point<float>;
template class Point<double>;
template class Point<int>;

} // namespace kdtrees
