#ifndef CSV_FILE_HANDLER_H_
#define CSV_FILE_HANDLER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

#include <points.h>
#include <node.h>

namespace kdtrees {

template<typename T>
class CsvFileHandler {
	public:
		CsvFileHandler() {}
		CsvFileHandler(std::string filename);
		~CsvFileHandler();
		Points<T> ReadPointsFromFile();
		void WriteTreeToFile(const Node<T>* node);
		void ReadTreeFromFile(Node<T>* temp);

	private:
		static const int NUM_NODE_ATTRIBUTES = 4;
		std::string m_filename; 
};

} // namespace kdtrees

#endif // CSV_FILE_HANDLER_H_