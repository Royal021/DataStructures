#include <graph_maker.h>
#include <graphs.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

// stack overflow helped me with the logic for the word separation as well as lowercasing every word, the rest is
//my previous experience with delimit anylizer

Graphmaker::Graphmaker(std::string fname) {
	mFile = fname;
}


bool Graphmaker::process()
{

	std::ifstream data_store;
	std::cout << "checking file:    " << mFile << std::endl;
	data_store.open(mFile.c_str());

	std::string line;
	char item;
	ssuds::Graph<std::string, std::string> outG;


	int found_word = 0;
	int found_apostrophe = 0;
	unsigned char c;
	std::string word;
	while (true)
	{
		if (data_store.eof())
		{
			break;
		}
		getline(data_store, line);
		
		

			c = line[0];

			if (i == 0)
			{
				if (c == 'n')
				{
					for (int i = 0; i < line.length(); i++) 
					{

					}

				}
				if (c == 'e')
				{

				}
			}

			if (!isalpha(c))
			{
				if (found_word) {
					if (!found_apostrophe && c == '\'') {
						found_apostrophe = 1;
					}
					else {
						found_apostrophe = 0;
						dC[word] = dC[word] + 1;
						word.clear();
						found_word = 0;
					}
				}
			}
			else
			{
				if (found_apostrophe)
				{
					word += '\'';
					found_apostrophe = 0;
				}
				found_word = 1;
				c = tolower(c);
				word += c;
			}


		
		if (word != "")
		{
			dC[word] = dC[word] + 1;
			word.clear();
		}
	}

	data_store.close();
	dC.makeResultsHowIWant();
	std::cout << "Files Done!" << std::endl;
	return true;

}
