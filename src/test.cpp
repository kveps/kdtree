#include <test.h>

namespace kdtrees {

void Test::TestPoint() {
	std::vector<std::vector<double>> pts_data = {{0.3, 1.2, 3.88}, {0.0, 1.0, 3.0}};
	Points<double> points(pts_data);

	Points<double>::PointList pt_mat = points.GetPoints();	

	points.PrintPoints();	
}

void Test::TestFileParser() {
	CsvFileHandler<double> file_parser("/home/karthik/kdtree/data/sample_data.csv");

	Points<double> pts = file_parser.ReadPointsFromFile();
	pts.PrintPoint(10);
}

void Test::TestBuildTree() {
	CsvFileHandler<double> file_parser("/home/karthik/kdtree/data/sample_data.csv");

	Points<double> pts = file_parser.ReadPointsFromFile();

	std::vector<std::vector<double>> pts_data = {{0.3, 1.2, 3.88}, {0.0, 1.0, 3.0},
												 {0.67, 1.0, 3.0}};
	Points<double>* points = new Points<double>(pts_data);
	
	BuildKdTree<double> tree(&pts);

	tree.WriteTreeToFile();

	delete points;
}

} // kdtrees