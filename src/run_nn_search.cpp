// standard includes
#include <iostream>

// project includes
#include <points.h>
#include <csv_file_handler.h>
#include <nearest_nbr_kd_tree.h>
#include <node.h>
#include <params.h>
#include <constants.h>

int main(int argc, char* argv[]){
	// Initialize all required objects
	kdtrees::CsvFileHandler<double> file_handler;
	kdtrees::Params params; 
	kdtrees::NodePtr<double> root(new kdtrees::Node<double>);
	kdtrees::PointsPtr<double> q_pts(new kdtrees::Points<double>());

	// Read params from config file
	kdtrees::utils::ReadParams(argv[1], params);

	// Update filename and read query points 
	file_handler.UpdateFileName(params.query_filename);
	file_handler.ReadPointsFromFile(q_pts);
	
	// Construct nearest neighbour search
	kdtrees::NearestNbrKdTree<double> nn_search(root, q_pts, params);
	
	// Update filename and read tree from file
	file_handler.UpdateFileName(params.tree_filename);
	nn_search.ReadTreeFromFile(&file_handler);

	// Nearest neighbour search
	nn_search.FindNearestPointInTree();

	// Update filename and write search results to file
	file_handler.UpdateFileName(params.nn_filename);
	nn_search.WriteNNSearchToFile(&file_handler);

	return 0;
}