#include <test.h>

namespace kdtrees {

Test::Test() {
	m_sample_filename = "/home/karthik/kdtree/data/sample_data.csv";
	m_query_filename = "/home/karthik/kdtree/data/query_data.csv";
	m_tree_filename = "/home/karthik/kdtree/data/tree.csv";
	m_nn_filename = "/home/karthik/kdtree/data/nn_search.csv";
} 

Test::~Test() {
}

void Test::TestPoint() {
	std::vector<std::vector<double>> pts_data = {{0.3, 1.2, 3.88}, {0.0, 1.0, 3.0}};
	Points<double> points(pts_data);
	Points<double>::PointList pt_mat = points.GetPoints();	
	points.PrintPoints();	
}

void Test::TestFileParser() {
	CsvFileHandler<double> file_parser(m_sample_filename);
	PointsPtr<double> pts(new Points<double>());
	file_parser.ReadPointsFromFile(pts);
	pts->PrintPoint(10);
}

void Test::TestBuildTree() {
	CsvFileHandler<double> file_handler;
	PointsPtr<double> s_pts(new Points<double>());
	NodePtr<double> root(new Node<double>);

	file_handler.UpdateFileName(m_sample_filename);
	file_handler.ReadPointsFromFile(s_pts);
	
	BuildKdTree<double> tree(root, s_pts);

	tree.RecursivelyBuildTree();
	
	file_handler.UpdateFileName(m_tree_filename);
	tree.WriteTreeToFile(&file_handler);
}

void Test::TestSearchNNTree() {
	CsvFileHandler<double> file_handler;
	NodePtr<double> root(new Node<double>);
	PointsPtr<double> q_pts(new Points<double>());

	file_handler.UpdateFileName(m_query_filename);
	file_handler.ReadPointsFromFile(q_pts);
	
	NearestNbrKdTree<double> nn_search(root, q_pts);
	
	file_handler.UpdateFileName(m_tree_filename);
	nn_search.ReadTreeFromFile(&file_handler);

	nn_search.FindNearestPointInTree();

	file_handler.UpdateFileName(m_nn_filename);
	nn_search.WriteNNSearchToFile(&file_handler);
}

void Test::TestFullPipeLine() {
	CsvFileHandler<double> file_handler;
	PointsPtr<double> s_pts(new Points<double>());
	PointsPtr<double> q_pts(new Points<double>());
	NodePtr<double> root(new Node<double>);

	file_handler.UpdateFileName(m_sample_filename);
	file_handler.ReadPointsFromFile(s_pts);
	
	BuildKdTree<double> tree(root, s_pts);

	tree.RecursivelyBuildTree();

	file_handler.UpdateFileName(m_query_filename);
	file_handler.ReadPointsFromFile(q_pts);

	NearestNbrKdTree<double> nn_search(root, s_pts, q_pts);

	nn_search.FindNearestPointInTree();

	file_handler.UpdateFileName(m_nn_filename);
	nn_search.WriteNNSearchToFile(&file_handler);
}

} // kdtrees