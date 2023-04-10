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
#include <gtest\gtest.h>

int main(int argc, char** argv)
{
 
    ssuds::OrderedSet<float> fset;
    bool added = fset.insert(4.4f);
    added = fset.insert(1.1f);		// added is true
    added = fset.insert(2.3f);			// added is true
    added = fset.insert(1.1f);		    // added is false
    added = fset.insert(4.3f);
    added = fset.insert(5.3f);
    added = fset.insert(6.3f);
    added = fset.insert(3.3f);
    added = fset.insert(1.3f);
    added = fset.insert(0.3f);
    added = fset.insert(1.4f);
    
 
    std::cout << fset.traversal(ssuds::traversalType::PRE) << std::endl;
    std::cout << fset.traversal(ssuds::traversalType::POST) << std::endl;
    std::cout << fset.traversal(ssuds::traversalType::IN) << std::endl;
  
   ssuds::OrderedSet<float> Fset;
   bool added1 = Fset.insert(4.4f);
   added1 = Fset.insert(1.1f);		// added is true
   added1 = Fset.insert(2.3f);			// added is true
   added1 = Fset.insert(4.3f);
   added1 = Fset.insert(5.3f);
   added1 = Fset.insert(6.3f);
   added1 = Fset.insert(3.3f);
   added1 = Fset.insert(1.3f);
   
   
   std::cout << Fset.traversal(ssuds::traversalType::PRE) << "yay" << std::endl;
   

   ssuds::OrderedSet<float>::OrderedSetIterator it = Fset.begin();
   while (it != Fset.end())
   {
       std::cout << *it << "\n";
       ++it;
   }
    /// hash ("bob) % mcap
    testing::InitGoogleTest();
    RUN_ALL_TESTS();  

}