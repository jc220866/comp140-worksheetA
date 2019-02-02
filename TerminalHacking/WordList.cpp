#include "stdafx.h"
#include "TerminalGame.h"

const std::string wordFileName("word-list.txt");

// Constructor. Reads the .txt file and fills a vector with words of the appropriate length.
FWordList::FWordList(int wordLength)
{
	std::ifstream wordFile(wordFileName);
	std::string word;

	// Read past the copyright notice at the top of words.txt
	while (std::getline(wordFile, word) && word != "---")
	{
		// do nothing
	}

	while (std::getline(wordFile, word)) // Read each line in the file
	{
		if (word.length() == wordLength)
		{
			// Scan through the line, converting each character to upper case.
			// If a non-alphabet character is encountered, reject the word.
			bIsValid = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (isalpha(word[i]))
				{
					word[i] = toupper(word[i]);
				}
				else
				{
					bIsValid = false;
					break;
				}
			}
			if (bIsValid)
			{
				validWords.push_back(word); // If it's a good word, add it to the list.
			}
		}
	}
}

// Returns a string containing a word randomly selected from the loaded .txt file
std::string FWordList::chooseRandomWord()
{
	int index = rand() % validWords.size();
	return validWords[index];
}
