#ifndef PARAMS_H_
#define PARAMS_H_

//system includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace kdtrees {

// \brief Holds all input into the executable
// TODO(Karthik) : Add axis and poisition selection
struct Params {
	std::string sample_filename;
	std::string query_filename;
	std::string tree_filename;
	std::string nn_filename;
	double nn_max_dist;
	unsigned int max_points_per_leaf;
};

namespace utils {

// \brief Read all params from the params config file
// TODO(Karthik) : Currently can only read from a structure
// Generalize to read from any config file
inline void ReadParams(std::string filename, Params& input_params) {
	std::ifstream file(filename);
	std::string line;
	std::string cell;

	unsigned int count = 0;

	while(file) {
		while(std::getline(file, line)) {
			count++;
			if(count <= 5 || (count % 2 != 0)) {
				continue;
			}
			std::stringstream line_stream(line);

			switch(count) {
				case 6:
					while(std::getline(line_stream, cell, ',')) {
						input_params.sample_filename = cell;
					}
					break;
				case 8:
					while(std::getline(line_stream, cell, ',')) {
						input_params.query_filename = cell;
					}
					break;
				case 10:
					while(std::getline(line_stream, cell, ',')) {
						input_params.tree_filename = cell;
					}
					break;
				case 12:
					while(std::getline(line_stream, cell, ',')) {
						input_params.nn_filename = cell;
					}
					break;
				case 14:
					while(std::getline(line_stream, cell, ',')) {
						input_params.nn_max_dist = atof(cell.c_str());
					}
					break;
				case 16:
					while(std::getline(line_stream, cell, ',')) {
						input_params.max_points_per_leaf = atoi(cell.c_str());
					}
					break;
			}
		}
	}	
}

} // namespace utils

} // namespace kdtrees

#endif // PARAMS_H_