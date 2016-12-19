#ifndef POINTS_H_
#define POINTS_H_

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

namespace kdtrees {

template<typename T>
class Points {
	public:
		typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> PointList;
		typedef Eigen::Matrix<T, 1, Eigen::Dynamic> Point;
		
		Points();
		Points(const Points<T> &pts);
		Points(std::vector<std::vector<T>> data);
		~Points();
		void FillPoints(std::vector<std::vector<T>> data);
		void StoreEigenVector(std::vector<std::vector<T>> data);
		void PrintPoints() const;
		void PrintPoint(int m) const;
		PointList GetPoints() const;
		Point GetPoint(unsigned int m) const;
		T GetPointValAtIndex(unsigned int m, unsigned int n) const;
		PointList GetColumn(unsigned int n) const;
		unsigned int GetPointDim() const;
		unsigned int GetPointsSize() const;

	private:
		PointList m_data;
};

template<typename T>
using PointsPtr = std::shared_ptr<Points<T>>;

} // namespace kdtrees

#endif // POINT_H_