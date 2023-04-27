#include <FrequencyMap.h>
#include <unordered_map.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

// stack overflow helped me with the logic for the word separation as well as lowercasing every word, the rest is
//my previous experience with delimit anylizer

FrequencyMap::FrequencyMap(std::string fname) {
	mFile = fname;
}


bool FrequencyMap::process()
{

	std::ifstream data_store;
	std::cout << "checking file:    " << mFile << std::endl;
	data_store.open(mFile.c_str());

	std::string line;
	char item;
	ssuds::UnorderedMap<std::string, int> dC;


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

		for (int i = 0; i < line.length(); i++) {

			c = line[i];

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


		}
		if (word != "")
		{
			dC[word] = dC[word] + 1;
			word.clear();
		}
	}

	data_store.close();
	dC.makeResultsHowIWant();
	std::cout << "Books Done!" << std::endl;
	return true;

}
