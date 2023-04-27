#pragma once
#include <unordered_map.h>
#include <iostream>
#include <fstream>

/// <summary>
/// a class for evaluating text docs by word
/// </summary>
class FrequencyMap
{
public:
	/// <summary>
	/// Frequency map constructor
	/// </summary>
	/// <param name="fname"></param> a files name as a std::string
	FrequencyMap(std::string  fname);

	/// <summary>
	/// function that does all the work in analyzing the file and sending it out to another
	/// </summary>
	/// <returns></returns> true or false, also sends out a message 
	bool process();

protected:

	/// <summary>
	/// the file stored as a string
	/// </summary>
	std::string mFile;

};