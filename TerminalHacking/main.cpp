#include "stdafx.h"
#include "WordList.h"
#include "TerminalGame.h"

FTerminalGame game;

int main()
{
	// Initialise word list
	FWordList words(game.GetWordLength());

	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Choose secret word
	std::string secretWord = words.getRandomWord();

	// Create a set to hold the list of options
	std::set<std::string> options;

	// Put the secret word in the set
	options.insert(secretWord);

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (options.size() < game.GetNumberOfWords())
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}


	// Display secret word at the top of the screen
	std::cout << secretWord << std::endl << std::endl;


	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}

	// TODO: implement the rest of the game

	return 0;
}
