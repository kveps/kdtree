#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <vector>
#include <stdexcept>

#include <Eigen/Core>

namespace kdtrees {

template<typename T>
class Point {
	public:
		Point() {}
		Point(std::vector<T> data);
		~Point();
		void FillPoint(std::vector<T> data);
		void PrintPoint();
		Eigen::VectorX<T> GetPoint();
		T GetPoint(int n);
		size_t GetPointDim();

	private:
		Eigen::VectorX<T> m_data;
};

} // namespace kdtrees

#endif // POINT_H_