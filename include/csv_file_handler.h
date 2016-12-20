#ifndef CSV_FILE_HANDLER_H_
#define CSV_FILE_HANDLER_H_

// standard includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>

// project includes
#include <points.h>
#include <node.h>
#include <params.h>
#include <constants.h>

namespace kdtrees {

// \brief Handles read write operations of CSV files
template<typename T>
class CsvFileHandler {
	public:

		CsvFileHandler() {}
		CsvFileHandler(std::string filename);
		~CsvFileHandler();
		void UpdateFileName(std::string filename);
		void ReadPointsFromFile(PointsPtr<T> points);
		void WriteTreeToFile(NodePtr<T> node,
							 const PointsPtr<T> points);
		void ReadTreeFromFile(std::vector<NodePtr<T>>& node_vec,
							  PointsPtr<T> points);
		void WriteNNSearchToFile(const std::vector<unsigned int> best_inds,
								 const std::vector<T> best_dists);

	private:

		// CSV filename
		std::string m_filename; 
};

} // namespace kdtrees

#endif // CSV_FILE_HANDLER_H_