#include <csv_file_parser.h>	

namespace kdtrees {

CsvFileParser::CsvFileParser(std::string filename) {
	ReadFile(filename);
}

CsvFileParser::~CsvFileParser() {
	m_data.clear();
}

void CsvFileParser::ReadFile(std::string filename) {
	std::ifstream file(filename.c_str());

	while(file) {
		std::string line;
		
		while(std::getline(file, line)) {
			std::vector<double> line_nums;
			std::string cell;
			std::stringstream line_stream(line);
		
			while(std::getline(line_stream, cell, ',')) {
				line_nums.push_back(atof(cell.c_str()));
			}

			m_data.push_back(Point<double>(line_nums));
		}
	}
}

std::vector<Point<double>> CsvFileParser::GetFileData() {
	return m_data;
}

Point<double> CsvFileParser::GetFileDataByLine(int n) {
	if(n >= m_data.size()) {
		throw std::invalid_argument("Input argument greater than size");
	}

	return m_data[n-1];
}

} // kdtrees