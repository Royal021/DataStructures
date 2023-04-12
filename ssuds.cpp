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
   // I had these here so it was easier to see they worked, there are google tests for them as well
   ssuds::OrderedSet<float> Fset;
   bool added1 = Fset.insert(4.4f);
   added1 = Fset.insert(1.1f);		
   added1 = Fset.insert(2.3f);			
   added1 = Fset.insert(4.3f);
   added1 = Fset.insert(5.3f);
   added1 = Fset.insert(6.3f);
   added1 = Fset.insert(3.3f);
   added1 = Fset.insert(1.3f);
   added1 = Fset.insert(61.3f);


   ssuds::OrderedSet<float>::OrderedSetIterator it = Fset.begin();
   while (it != Fset.end())
   {
       std::cout << *it << "\n";
       ++it;
   }
    /// hash ("bob) % mcap


   std::string tstring = Fset.tree_string();
   std::cout << tstring << std::endl;
    testing::InitGoogleTest();
    RUN_ALL_TESTS();  

}