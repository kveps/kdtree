#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <vector>
#include <stdexcept>

namespace kdtrees {

template<typename T>
class Point {
	public:
		Point() {}
		Point(std::vector<T> data);
		~Point();
		void FillPoint(std::vector<T> data);
		void PrintPoint();
		std::vector<T> GetPoint();
		T GetPoint(int n);

	private:
		std::vector<T> m_data;
};

} // namespace kdtrees

#endif // POINT_H_