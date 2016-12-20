// standard includes
#include <iostream>

// project includes
#include <test.h>

int main(int argc, char* argv[]){
	// Params object
	kdtrees::Params params;

	// Read params from config file
	kdtrees::utils::ReadParams(argv[1], params);

	// Construct test object
	kdtrees::Test test(params);

	// Test full pipeline
	test.TestFullPipeLine();

	return 0;
}