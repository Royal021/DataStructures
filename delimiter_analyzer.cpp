#include <delimiter_analyzer.h>
#include <queue.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

/// <summary>
/// The Delimiter Analyzer Constructor
/// </summary>
/// <param name="fname"></param> A filename as a std::string
DelimiterAnalyzer::DelimiterAnalyzer(std::string fname) {
	mFile = fname;
}

/// <summary>
/// The real hero, a function to process the file in question
/// </summary>
/// <returns></returns> true or false, also outputs some text
bool DelimiterAnalyzer::process()
{
	std::ifstream data_store;
	std::cout << "checking file:    " << mFile << std::endl;
	data_store.open(mFile.c_str());

	std::string line;
	char item;
	ssuds::Stack<char> DAStack;
	int stringy = 1;
	while (true)
	{
		if (data_store.eof())
		{
			break;
		}
		getline(data_store, line);

		for (int i = 0; i < line.length(); i++) {
			item = line[i];
			if (item == '"')
			{
				stringy *= -1;
			}
			if (stringy > 0)
			{
				if (item == '#' || item == '!')
				{
					break;
				}
				else if (item == '(' || item == '{' || item == '[')
				{
					DAStack.push(item);
				}
				else if (item == ')')
				{
					if (DAStack.empty() == 1)
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}
					else if (DAStack.top() == '(' && DAStack.empty() == 0)
					{
						DAStack.pop();
					}
					else
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}
				}
				else if (item == '}')
				{
					if (DAStack.empty() == 1)
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}

					if (DAStack.top() == '{')
					{
						DAStack.pop();
					}
					else
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}

				}
				else if (item == ']')
				{
					if (DAStack.empty() == 1)
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}
					if (DAStack.top() == '[')
					{
						DAStack.pop();
					}
					else
					{
						std::cout << "This file is bad!" << std::endl;
						return false;
					}
				}
				else { ; }
			}
		}
	}

	data_store.close();
	std::cout << "This file is good!" << std::endl;
	return true;


}
