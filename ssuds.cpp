#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <stdexcept>
#include <fstream>
#include <array_list.h>
#include <array_list_utility.h>
#include <stack.h>   
#include <queue.h>
#include <ordered_set.h>
#include <delimiter_analyzer.h>
#include <unordered_map.h>
#include <gtest\gtest.h>
#include <FrequencyMap.h>
#include <graphs.h>

//I threw some readable checks in this main, the tests do everything as well.
int main(int argc, char** argv)
{
    ssuds::Graph<int, float> g;
    g.add_node(6);
    g.add_node(2);
    g.add_node(4);
    g.add_node(1);
    g.add_edge(3.3f, 1, 2);
    g.add_edge(3.1f, 1, 4);
    g.add_edge(1.1f, 6, 2);
    g.add_edge(3.5f, 6, 4);
    g.add_edge(234.1f, 1, 2);
   
    
    std::cout << "this is the og graph"<<std::endl<<  g << std::endl;
    g.remove_node(1);
    std::cout << "this is removed 1 node" << std::endl << g << std::endl;
    g.remove_edge(6, 4);
    std::cout << "this is removed 6 and 4 edge" << std::endl << g << std::endl;

    testing::InitGoogleTest();
    RUN_ALL_TESTS();  
}