#ifndef CSV_FILE_PARSER_H_
#define CSV_FILE_PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <point.h>

namespace kdtrees {

class CsvFileParser {
	public:
		CsvFileParser() {}
		CsvFileParser(std::string filename);
		~CsvFileParser();
		void ReadFile(std::string filename);
		std::vector<Point<double>> GetFileData();
		Point<double> GetFileDataByLine(int n);

	private:
		std::vector<Point<double>> m_data; 
};

} // namespace kdtrees

#endif // CSV_FILE_PARSER_H_