#include <gtest/gtest.h>
#include <array_list.h>
#include <linked_list.h>
#include <stack.h>
#include <queue.h>
#include <ordered_set.h>

#define EXECUTE_LINKED_LIST_TESTS 0
#define EXECUTE_STACK_TESTS 0
#define EXECUTE_QUEUE_TESTS 0
#define EXECUTE_SET_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS

class LinkedListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.prepend("B");
		slist2.append("C");
		slist2.insert("A", 0);
		slist2.insert("D", 3);
	}

	void TearDown() override
	{

	}


	ssuds::LinkedList<std::string> slist1;
	ssuds::LinkedList<std::string> slist2;
	ssuds::LinkedList<int> ilist;
};

TEST_F(LinkedListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
	EXPECT_EQ(ilist.size(), 0);
}


TEST_F(LinkedListTestFixture, AddingItems)
{
	ASSERT_EQ(slist2.size(), 4);
	EXPECT_EQ(slist2[0], "A");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_EQ(slist2[2], "C");
	EXPECT_EQ(slist2[3], "D");
}


TEST_F(LinkedListTestFixture, EmptyManualIteration)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist1.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist1.end();
	ASSERT_EQ(it, it_end);
}


TEST_F(LinkedListTestFixture, ManualIteration)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist2.end();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, "A");
	val2 = *it;
	++it;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val2, "B");
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4, "D");
	EXPECT_EQ(it, it_end);
}

TEST_F(LinkedListTestFixture, PrettyIteration)
{
	int i = 0;
	for (std::string s : slist2)
	{
		if (i == 0)
			EXPECT_EQ(s, "A");
		else if (i == 1)
			EXPECT_EQ(s, "B");
		else if (i == 2)
			EXPECT_EQ(s, "C");
		else
			EXPECT_EQ(s, "D");
		i++;
	}
}


TEST_F(LinkedListTestFixture, OS_Stream)
{
	std::stringstream ss;
	ss << slist1;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(std::string());
	ss << slist2;
	EXPECT_EQ(ss.str(), "[A, B, C, D]");
}

TEST_F(LinkedListTestFixture, FindingARealValue)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.find("C");
	std::string val1, val2, val3, val4;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4, "D");
}

TEST_F(LinkedListTestFixture, RemovingAvalue)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.find("C");
	std::string val1, val2, val3, val4, val4b;
	val3 = *it;
	ssuds::LinkedList<std::string>::LinkedListIterator it2 = slist2.remove(it);
	val4b = *it2;
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4b, "D");
	EXPECT_EQ(slist2.size(), 3);
}

TEST_F(LinkedListTestFixture, RemovingAvalueAtEnd)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.find("D");
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist2.end();
	std::string val1, val2, val3, val4, val4b;
	val3 = *it;
	ssuds::LinkedList<std::string>::LinkedListIterator it2 = slist2.remove(it);
	++it;
	EXPECT_EQ(val3, "D");
	EXPECT_EQ(it,it_end );
	EXPECT_EQ(slist2.size(), 3);
}

TEST_F(LinkedListTestFixture, RemovingAvalueatBegin)
{
	std::string val1, val2, val3, val4, val4b;
	ssuds::LinkedList<std::string>::LinkedListIterator it2 = slist2.remove(slist2.begin());
	val4b = *it2;
	EXPECT_EQ(val4b, "B");
	EXPECT_EQ(slist2.size(), 3);
}


TEST_F(LinkedListTestFixture, FindingAUnrealValue)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.find("k");
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist2.end();
	EXPECT_EQ(it, it_end);
}


TEST_F(LinkedListTestFixture, CopyConstructor)
{
	ssuds::LinkedList<std::string> slist_copy1 = slist2;
	ssuds::LinkedList<std::string> slist_copy2(slist2);
	ASSERT_EQ(slist_copy1.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy1.size(), 4);

	
	ASSERT_EQ(slist_copy2.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy2.size(), 4);
}


TEST_F(LinkedListTestFixture, Assignment)
{
	ssuds::LinkedList<std::string> slist3;
	slist3.append("X");
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], "X");
	slist3 = slist2;
	ASSERT_EQ(slist3.size(), 4);
	EXPECT_EQ(slist3[0], "A");
	EXPECT_EQ(slist3[1], "B");
	EXPECT_EQ(slist3[2], "C");
	EXPECT_EQ(slist3[3], "D");
	EXPECT_EQ(slist3.size(), 4);
}


TEST_F(LinkedListTestFixture, InitializerListConstructor)
{
	ssuds::LinkedList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}


ssuds::LinkedList<float> move_func()
{
	ssuds::LinkedList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}

TEST_F(LinkedListTestFixture, MoveConstructor)
{
	ssuds::LinkedList<float> my_arr = move_func();
	ASSERT_EQ(my_arr.size(), 2);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
}

#endif

#if EXECUTE_STACK_TESTS
class StackTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		stack1.push(1);
		stack1.push(2);
		stack1.push(3);
		stack1.push(5);
		stack1.push(7);
		stack1.push(11);
	}

	void TearDown() override
	{

	}


	ssuds::Stack<int> stack1;
	ssuds::Stack<int> stack2;
	ssuds::Stack<int> stackempty;
	ssuds::Stack<std::string> stringStack;
};

TEST_F(StackTestFixture, EmptyFunctionality)
{
	EXPECT_EQ(stackempty.empty(), 1);
	EXPECT_EQ(stack1.empty(), 0);
}

TEST_F(StackTestFixture, clearAllFunction)
{
	ssuds::Stack<int> test_stack;
	test_stack.push(3);
	test_stack.push(5);
	test_stack.push(6);
	test_stack.push(7);
	test_stack.clearall();
	EXPECT_EQ(test_stack.empty(), 1);
}

TEST_F(StackTestFixture, PushandTop)
{
	ssuds::Stack<int> test_stack;
	test_stack.push(3);
	test_stack.push(5);
	test_stack.push(6);
	test_stack.push(7);
	EXPECT_EQ(test_stack.top(), 7);
}

TEST_F(StackTestFixture, PushandPop)
{
	ssuds::Stack<int> test_stack;
	test_stack.push(3);
	test_stack.push(5);
	test_stack.push(6);
	test_stack.push(7);
	std::stringstream ss;
	EXPECT_EQ(test_stack.top(), 7);
	test_stack.pop();
	test_stack.pop();
	ss.str("");
	ss << test_stack; 
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[5, 3]");	
}

TEST_F(StackTestFixture, osstream)
{
	ssuds::Stack<int> test_stack;
	test_stack.push(3);
	test_stack.push(5);
	test_stack.push(6);
	test_stack.push(7);
	std::stringstream ss;
	EXPECT_EQ(test_stack.top(), 7);
	ss.str("");
	ss << test_stack;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[7, 6, 5, 3]");
}

TEST_F(StackTestFixture, Iterator)
{
	ssuds::Stack<std::string> stringstack;
	stringstack.push("NFL");
	stringstack.push("MBA");
	stringstack.push("MLB");
	stringstack.push("MLS");
	ssuds::Stack<std::string>::LinkedListIterator it = stringstack.begin(); //1,2,3,5,7,11
	ssuds::Stack<std::string>::LinkedListIterator itEnd = stringstack.end();
	EXPECT_EQ(*it, "MLS");
	++it;
	EXPECT_EQ(*it, "MLB");
	++it;
	EXPECT_EQ(*it, "MBA");
	++it;
	EXPECT_EQ(*it, "NFL");
	++it;
	EXPECT_EQ(it, itEnd);
}

#endif

#if EXECUTE_QUEUE_TESTS
class QueueTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		queue1.enqueue(1.1f);
		queue1.enqueue(5.5f);
		queue1.enqueue(3.3f);
		queue1.enqueue(12.11f);
	}

	void TearDown() override
	{

	}


	ssuds::Queue<float> queue1;
	ssuds::Queue<float> queue2;
	ssuds::Queue<float> emptyQueue;
	
};

TEST_F(QueueTestFixture, EmptyFunctionality)
{
	EXPECT_EQ(emptyQueue.empty(), 1);
	EXPECT_EQ(queue1.empty(), 0);
}

TEST_F(QueueTestFixture, clearAllFunction)
{
	queue1.clear();
	EXPECT_EQ(queue1.empty(), 1);
}

TEST_F(QueueTestFixture, Head)
{
	EXPECT_EQ(queue1.head(), 1.1f);
	queue1.dequeue();
	EXPECT_EQ(queue1.head(), 5.5f);
}

TEST_F(QueueTestFixture, PushandPop)
{
	ssuds::Queue<int> test_queue;
	test_queue.enqueue(3);
	test_queue.enqueue(5);
	test_queue.enqueue(6);
	test_queue.enqueue(7);
	std::stringstream ss;
	EXPECT_EQ(test_queue.head(), 3);
	test_queue.dequeue();
	test_queue.dequeue();
	ss.str("");
	ss << test_queue;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[6, 7]");
}

TEST_F(QueueTestFixture, osstream)
{
	
	std::stringstream ss;
	EXPECT_EQ(queue1.head(), 1.1f);
	ss.str("");
	ss << queue1;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[1.1, 5.5, 3.3, 12.11]");
}

TEST_F(QueueTestFixture, Iterator)
{
	ssuds::Queue<std::string> stringqueue;
	stringqueue.enqueue("NFL");
	stringqueue.enqueue("MBA");
	stringqueue.enqueue("MLB");
	stringqueue.enqueue("MLS");
	ssuds::Stack<std::string>::LinkedListIterator it = stringqueue.begin(); //1,2,3,5,7,11
	ssuds::Stack<std::string>::LinkedListIterator itEnd = stringqueue.end();
	EXPECT_EQ(*it, "NFL");
	++it;
	EXPECT_EQ(*it, "MBA");
	++it;
	EXPECT_EQ(*it, "MLB");
	++it;
	EXPECT_EQ(*it, "MLS");
	++it;
	EXPECT_EQ(it, itEnd);
}
#endif


#if EXECUTE_SET_TESTS
class SetTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		bool added = Fset.insert(4.4f);
		added = Fset.insert(1.1f);		// added is true
		added = Fset.insert(2.3f);			// added is true
		added = Fset.insert(4.3f);
		added = Fset.insert(5.3f);
		added = Fset.insert(6.3f);
		added = Fset.insert(3.3f);
		added = Fset.insert(1.3f);
		bool addedString = Sset.insert("moth");
		addedString = Sset.insert("dog");
		addedString = Sset.insert("cat");
		addedString = Sset.insert("zebra");
		addedString = Sset.insert("lion");
		addedString = Sset.insert("aardvark");
	}

	void TearDown() override
	{

	}


	ssuds::OrderedSet<float> Fset;
	ssuds::OrderedSet<std::string> Sset;
	ssuds::OrderedSet<float> Emptyset;

};

TEST_F(SetTestFixture, ClearFunctionality)
{
	std::stringstream ss;
	ss.str("");
	Fset.clear();
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[]");
}


TEST_F(SetTestFixture, traversal_pre)
{
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[4.4, 1.1, 2.3, 1.3, 4.3, 3.3, 5.3, 6.3]");
}

TEST_F(SetTestFixture, traversal_post)
{
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::POST);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[1.3, 3.3, 4.3, 2.3, 1.1, 6.3, 5.3, 4.4]");
}

TEST_F(SetTestFixture, traversal_in)
{
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::IN);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[1.1, 1.3, 2.3, 3.3, 4.3, 4.4, 5.3, 6.3]");
}


TEST_F(SetTestFixture, rebalance)
{
	std::stringstream ss;
	ss.str("");
	Fset.rebalance();
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[3.3, 1.3, 1.1, 2.3, 4.4, 4.3, 5.3, 6.3]");
}

TEST_F(SetTestFixture, contains)
{
	EXPECT_TRUE(Fset.contains(4.4f));
	EXPECT_TRUE(Fset.contains(6.3f));
	EXPECT_TRUE(Fset.contains(3.3f));
	EXPECT_FALSE(Fset.contains(5.1234f));
}

TEST_F(SetTestFixture, getHeight)
{
	EXPECT_EQ(Fset.get_height(), 5);
	Fset.rebalance();
	EXPECT_EQ(Fset.get_height(), 4);
}

TEST_F(SetTestFixture, removeMiddle)
{
	EXPECT_TRUE(Fset.erase(1.1f));
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[4.4, 2.3, 1.3, 4.3, 3.3, 5.3, 6.3]");
}


TEST_F(SetTestFixture, removeEnd)
{
	EXPECT_TRUE(Fset.erase(6.3f));
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[4.4, 1.1, 2.3, 1.3, 4.3, 3.3, 5.3]");
}

TEST_F(SetTestFixture, removeTop)
{
	EXPECT_TRUE(Fset.erase(4.4f));
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[5.3, 1.1, 2.3, 1.3, 4.3, 3.3, 6.3]");
}

TEST_F(SetTestFixture, removeALot)
{
	EXPECT_TRUE(Fset.erase(4.4f));
	
	EXPECT_TRUE(Fset.erase(3.3f));
	
	EXPECT_TRUE(Fset.erase(5.3f)); //funny guy
	
	EXPECT_TRUE(Fset.erase(1.1f));
	
	std::stringstream ss;
	ss.str("");
	ss << Fset.traversal(ssuds::traversalType::PRE);
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[6.3, 2.3, 1.3, 4.3]");
}

TEST_F(SetTestFixture, Intersection)
{
	ssuds::OrderedSet<float> fset;
	bool added = fset.insert(4.4f);
	added = fset.insert(1.1f);		
	added = fset.insert(2.3f);			
	added = fset.insert(4.3f);
	added = fset.insert(5.3f);
	added = fset.insert(6.3f);
	added = fset.insert(3.3f);
	added = fset.insert(1.3f);
	added = fset.insert(0.3f);			//diff
	added = fset.insert(1.4f);			//diff


	ssuds::OrderedSet<float> Fset;
	bool added1 = Fset.insert(4.4f);
	added1 = Fset.insert(1.1f);		
	added1 = Fset.insert(2.3f);			
	added1 = Fset.insert(4.3f);
	added1 = Fset.insert(5.3f);
	added1 = Fset.insert(6.3f);
	added1 = Fset.insert(3.3f);
	added1 = Fset.insert(1.3f);
	added1 = Fset.insert(61.3f);		//diff

	ssuds::ArrayList<float> Inti = Fset.Intersection(fset);

	std::stringstream ss;
	ss.str("");
	ss << Inti;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[1.1, 1.3, 2.3, 3.3, 4.3, 4.4, 5.3, 6.3]");
}

TEST_F(SetTestFixture, Union)
{
	ssuds::OrderedSet<float> fset;
	bool added = fset.insert(4.4f);
	added = fset.insert(1.1f);
	added = fset.insert(2.3f);
	added = fset.insert(4.3f);
	added = fset.insert(5.3f);
	added = fset.insert(6.3f);
	added = fset.insert(3.3f);
	added = fset.insert(1.3f);
	added = fset.insert(0.3f);			//diff
	added = fset.insert(1.4f);			//diff


	ssuds::OrderedSet<float> Fset;
	bool added1 = Fset.insert(4.4f);
	added1 = Fset.insert(1.1f);
	added1 = Fset.insert(2.3f);
	added1 = Fset.insert(4.3f);
	added1 = Fset.insert(5.3f);
	added1 = Fset.insert(6.3f);
	added1 = Fset.insert(3.3f);
	added1 = Fset.insert(1.3f);
	added1 = Fset.insert(61.3f);		//diff

	ssuds::ArrayList<float> Uni = Fset.Union(fset);

	std::stringstream ss;
	ss.str("");
	ss << Uni;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[0.3, 1.1, 1.3, 1.4, 2.3, 3.3, 4.3, 4.4, 5.3, 6.3, 61.3]");
}

TEST_F(SetTestFixture, RelativeDifference)
{
	ssuds::OrderedSet<float> fset;
	bool added = fset.insert(4.4f);
	added = fset.insert(1.1f);
	added = fset.insert(2.3f);
	added = fset.insert(4.3f);
	added = fset.insert(5.3f);
	added = fset.insert(6.3f);
	added = fset.insert(3.3f);
	added = fset.insert(1.3f);
	added = fset.insert(0.3f);			//diff
	added = fset.insert(1.4f);			//diff


	ssuds::OrderedSet<float> Fset;
	bool added1 = Fset.insert(4.4f);
	added1 = Fset.insert(1.1f);
	added1 = Fset.insert(2.3f);
	added1 = Fset.insert(4.3f);
	added1 = Fset.insert(5.3f);
	added1 = Fset.insert(6.3f);
	added1 = Fset.insert(3.3f);
	added1 = Fset.insert(1.3f);
	added1 = Fset.insert(61.3f);		//diff

	ssuds::ArrayList<float> rdf = Fset.RelativeDifference(fset);

	std::stringstream ss;
	ss.str("");
	ss << rdf;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "[1.4, 0.3]");
}

TEST_F(SetTestFixture, TreeString)
{
	std::string tstring = Fset.tree_string();
	std::stringstream ss;
	ss.str("");
	ss << tstring;
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "4.400000\n   L:1.100000\n      R:2.300000\n         L:1.300000\n         R:4.300000\n            L:3.300000\n   R:5.300000\n      R:6.300000");
}


TEST_F(SetTestFixture, Iterator)
{
	std::stringstream ss;
	ss.str("");
	
	ssuds::OrderedSet<float>::OrderedSetIterator it = Fset.begin();
	while (it != Fset.end())
	{
		ss << *it << ' ';
		++it;
	}
	
	std::string ss_captured_string = ss.str();
	EXPECT_EQ(ss_captured_string, "1.1 1.3 2.3 3.3 4.3 4.4 5.3 6.3 ");
}

TEST_F(SetTestFixture, copyConstruct)
{
	ssuds::OrderedSet<std::string> OSS = Sset;
	ssuds::ArrayList<std::string> SsetAR = Sset.traversal(ssuds::traversalType::PRE);
	ssuds::ArrayList<std::string> OSSAR = OSS.traversal(ssuds::traversalType::PRE);
	for (int i = 0; i < OSSAR.size(); i++)
	{
		ASSERT_EQ(OSSAR[i], SsetAR[i]);
	}
	OSS.insert("fools");
	ssuds::ArrayList<std::string> OSSAR2 = OSS.traversal(ssuds::traversalType::PRE);
	ssuds::ArrayList<std::string> SsetAR2 = Sset.traversal(ssuds::traversalType::PRE);
	ASSERT_EQ(OSS.size(), 7);
	ASSERT_EQ(Sset.size(), 6);
}

TEST_F(SetTestFixture, InitializerListConstructor)
{
	ssuds::OrderedSet<int> testSet{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(testSet.size(), 8);
	ssuds::ArrayList<int> test = testSet.traversal(ssuds::traversalType::PRE);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 3);
	EXPECT_EQ(test[2], 1);
	EXPECT_EQ(test[3], 0);
	EXPECT_EQ(test[4], 2);
	EXPECT_EQ(test[5], 8);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 9);
}

ssuds::OrderedSet<float> move_func()
{
	ssuds::OrderedSet<float> result;
	result.insert(3.1f);
	result.insert(4.2f);
	result.insert(1.3f);
	result.insert(0.3f);
	return result;
}

TEST_F(SetTestFixture, MoveConstructor)
{
	ssuds::OrderedSet<float> my_set = move_func();
	ASSERT_EQ(my_set.size(), 4);
	ssuds::ArrayList<float> my_arr = my_set.traversal(ssuds::traversalType::PRE);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 1.3f);
	EXPECT_EQ(my_arr[3], 4.2f);
	EXPECT_EQ(my_arr[2], 0.3f);
}
#endif