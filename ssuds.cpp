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
#include <gtest\gtest.h>

int main(int argc, char** argv)
{
    
    //std::cout << c.removeByIndex(2) << std::endl;
    //std::cout << c << std::endl;
    
    ssuds::Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(5);
    a.push(7);
    a.push(11);
    std::cout << a << std::endl;
    a.pop();
    a.pop();
    std::cout << a << std::endl;
    a.clearall();
    std::cout << a << std::endl;
    if (a.empty() == 1) {
        std::cout << "yeet" << std::endl;
    }

    ssuds::OrderedSet<float> fset;
    fset.traversal(ssuds::traversalType::PRE);
    bool added = fset.insert(4.4f);
    added = fset.insert(1.1f);		// added is true
    added = fset.insert(2.3f);			// added is true
    added = fset.insert(1.1f);		    // added is false
    added = fset.insert(4.3f);
    added = fset.insert(5.3f);
    added = fset.insert(6.3f);
    added = fset.insert(3.3f);
    added = fset.insert(1.3f);
    fset.traversal(ssuds::traversalType::PRE);
    std::cout << "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll" << std::endl;
    fset.traversal(ssuds::traversalType::POST);
    std::cout << "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll" << std::endl;
    fset.traversal(ssuds::traversalType::IN);
    testing::InitGoogleTest();
    RUN_ALL_TESTS();  

}