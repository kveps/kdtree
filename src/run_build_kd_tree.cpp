// standard includes
#include <iostream>

// project includes
#include <points.h>
#include <csv_file_handler.h>
#include <build_kd_tree.h>
#include <node.h>
#include <params.h>
#include <constants.h>

int main(int argc, char* argv[]){
	// Initialize all required objects
	kdtrees::CsvFileHandler<double> file_handler;
	kdtrees::Params params; 
	kdtrees::NodePtr<double> root(new kdtrees::Node<double>);
	kdtrees::PointsPtr<double> s_pts(new kdtrees::Points<double>());

	// Read params from config file
	kdtrees::utils::ReadParams(argv[1], params);

	// Update filename and read sample points 
	file_handler.UpdateFileName(params.sample_filename);
	file_handler.ReadPointsFromFile(s_pts);
	
	// Construct kd-tree and recursively build
	kdtrees::BuildKdTree<double> tree(root, s_pts, params);
	tree.RecursivelyBuildTree();
	
	// Update filename and write tree to file
	file_handler.UpdateFileName(params.tree_filename);
	tree.WriteTreeToFile(&file_handler);

	return 0;
}