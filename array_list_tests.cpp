#include <gtest/gtest.h>
#include <array_list.h>
#include <linked_list.h>
#include <stack.h>
#include <queue.h>

#define EXECUTE_LINKED_LIST_TESTS 0
#define EXECUTE_STACKED_QUEUE_TESTS 1
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

#if EXECUTE_STACKED_QUEUE_TESTS
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

TEST_F(StackTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(stackempty.empty(), 1);
	EXPECT_EQ(stack1.empty(), 0);
}

#endif