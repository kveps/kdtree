#ifndef TEST_H_
#define TEST_H_

#include <iostream>

#include <points.h>
#include <csv_file_handler.h>
#include <build_kd_tree.h>

namespace kdtrees {

class Test {
	public:
		Test() {}
		~Test() {}
		void TestPoint();
		void TestFileParser();
		void TestBuildTree();
};

} // namespace kdtrees

#endif // TEST_H_