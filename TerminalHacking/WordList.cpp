#include "stdafx.h"
#include "TerminalGame.h"

const std::string wordFileName("words.txt");

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
			bool isValid = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (isalpha(word[i]))
				{
					word[i] = toupper(word[i]);
				}
				else
				{
					isValid = false;
					break;
				}
			}

			if (isValid)
			{
				words.push_back(word); // If it's a good word, add it to the list.
			}
		}
	}
}

std::string FWordList::getRandomWord()
{
	int index = rand() % words.size();
	return words[index];
}