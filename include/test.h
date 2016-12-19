#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <string>

#include <points.h>
#include <csv_file_handler.h>
#include <build_kd_tree.h>
#include <nearest_nbr_kd_tree.h>
#include <node.h>

namespace kdtrees {

class Test {
	public:
		Test();
		~Test();
		void TestPoint();
		void TestFileParser();
		void TestBuildTree();
		void TestSearchNNTree();
		void TestFullPipeLine();
	
	private:
		std::string m_sample_filename;
		std::string m_query_filename;
		std::string m_tree_filename;
		std::string m_nn_filename;
};

} // namespace kdtrees

#endif // TEST_H_