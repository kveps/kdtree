#include <iostream>
#include <csv_file_parser.h>

using namespace kdtrees;

int main(){

	CsvFileParser file_parser("/home/karthik/kdtree/data/sample_data.csv");

	Point<double> pt = file_parser.GetFileDataByLine(10);

	pt.PrintPoint();

	return 0;
}