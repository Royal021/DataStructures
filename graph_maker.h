#pragma once
#include <stack.h>
#include <queue.h>
#include <iostream>
#include <fstream>

/// <summary>
/// a class for evaluating text docs like code
/// </summary>
class Graphmaker
{
public:
	/// <summary>
	/// analyzer constructor
	/// </summary>
	/// <param name="fname"></param> a files name as a std::string
	Graphmaker(std::string fname);

	/// <summary>
	/// function that does all the work in analyzing the file
	/// </summary>
	/// <returns></returns> true or false, also sends out a message 
	bool process();

protected:
	
	/// <summary>
	/// the file stored as a string
	/// </summary>
	std::string mFile;

};