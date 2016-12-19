#include <iostream>

#include <points.h>
#include <csv_file_handler.h>
#include <build_kd_tree.h>
#include <nearest_nbr_kd_tree.h>
#include <node.h>
#include <test.h>

using namespace kdtrees;

int main(){

	Test test;

	test.TestFullPipeLine();

	return 0;
}