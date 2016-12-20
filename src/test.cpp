#include <test.h>

namespace kdtrees {

// \brief Construct on params object
Test::Test(Params params)
:
m_params(params) {
} 

// \brief Destroy member variables
Test::~Test() {
}

// \brief Test point class and print
void Test::TestPoint() {
	// Test on hardcoded points
	std::vector<std::vector<double>> pts_data = {{0.3, 1.2, 3.88}, {0.0, 1.0, 3.0}};
	Points<double> points(pts_data);
	Points<double>::PointList pt_mat = points.GetPoints();	
	points.PrintPoints();	
}

// \brief Test reading points from a file
void Test::TestFileParser() {
	// test on sample points
	CsvFileHandler<double> file_parser(m_params.sample_filename);
	PointsPtr<double> pts(new Points<double>());
	file_parser.ReadPointsFromFile(pts);
	pts->PrintPoint(10);
}

// \brief Test building kd-tree
void Test::TestBuildTree() {
	// Initialize all required objects
	CsvFileHandler<double> file_handler;
	Params params; 
	NodePtr<double> root(new Node<double>);
	PointsPtr<double> s_pts(new Points<double>());

	// Update filename and read sample points 
	file_handler.UpdateFileName(m_params.sample_filename);
	file_handler.ReadPointsFromFile(s_pts);
	
	// Construct kd-tree and recursively build
	BuildKdTree<double> tree(root, s_pts, m_params);
	tree.RecursivelyBuildTree();
	
	// Update filename and write tree to file
	file_handler.UpdateFileName(m_params.tree_filename);
	tree.WriteTreeToFile(&file_handler);
}

// \brief Test nearest neighbour search 
// tree is read from input file
// prints final search results to file
void Test::TestSearchNNTree() {
	// Initialize all required objects
	CsvFileHandler<double> file_handler;
	Params params; 
	NodePtr<double> root(new Node<double>);
	PointsPtr<double> q_pts(new Points<double>());

	// Update filename and read query points 
	file_handler.UpdateFileName(m_params.query_filename);
	file_handler.ReadPointsFromFile(q_pts);
	
	// Construct nearest neighbour search
	NearestNbrKdTree<double> nn_search(root, q_pts, m_params);
	
	// Update filename and read tree from file
	file_handler.UpdateFileName(m_params.tree_filename);
	nn_search.ReadTreeFromFile(&file_handler);

	// Nearest neighbour search
	nn_search.FindNearestPointInTree();

	// Update filename and write search results to file
	file_handler.UpdateFileName(m_params.nn_filename);
	nn_search.WriteNNSearchToFile(&file_handler);
}

// \brief Test the entire pipeline 
// without printing tree to file
// prints final search results to file
void Test::TestFullPipeLine() {
	// Initialize all required objects
	CsvFileHandler<double> file_handler;
	PointsPtr<double> s_pts(new Points<double>());
	NodePtr<double> root(new Node<double>);
	PointsPtr<double> q_pts(new Points<double>());

	// Update filename and read sample points 
	file_handler.UpdateFileName(m_params.sample_filename);
	file_handler.ReadPointsFromFile(s_pts);
	
	// Construct kd-tree and recursively build
	BuildKdTree<double> tree(root, s_pts, m_params);
	tree.RecursivelyBuildTree();

	// Update filename and read query points 
	file_handler.UpdateFileName(m_params.query_filename);
	file_handler.ReadPointsFromFile(q_pts);

	// Construct nearest neighbour search
	NearestNbrKdTree<double> nn_search(root, s_pts,
									   q_pts, m_params);

	// Nearest neighbour search
	nn_search.FindNearestPointInTree();

	// Update filename and write search results to file
	file_handler.UpdateFileName(m_params.nn_filename);
	nn_search.WriteNNSearchToFile(&file_handler);
}

} // kdtrees