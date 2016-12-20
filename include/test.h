#ifndef TEST_H_
#define TEST_H_

// standard includes
#include <iostream>
#include <string>

// project includes
#include <points.h>
#include <csv_file_handler.h>
#include <build_kd_tree.h>
#include <nearest_nbr_kd_tree.h>
#include <node.h>
#include <params.h>
#include <constants.h>

namespace kdtrees {

// \brief Test class to individually test stuff
class Test {
	public:

		Test(Params params);
		~Test();
		void TestPoint();
		void TestFileParser();
		void TestBuildTree();
		void TestSearchNNTree();
		void TestFullPipeLine();
	
	private:

		// Params object
		Params m_params;
};

} // namespace kdtrees

#endif // TEST_H_