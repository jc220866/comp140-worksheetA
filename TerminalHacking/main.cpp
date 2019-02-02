#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame game; // Initialize game

int main()
{
	game.Reset();

	// Initialise list of appropriate possible words for chosen difficulty
	FWordList wordList(game.GetWordLength());

	AddSecretWord(wordList);
	AddDummyWords(wordList);
	PrintGameScreen();

	// TODO: implement the rest of the game

	return 0;
}

void AddSecretWord(FWordList wordList)
{
	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	// Choose secret word
	std::string secretWord = wordList.getRandomWord();

	// Put the secret word in the set
	game.allWords.insert(secretWord);



	// Display secret word at the top of the screen
	std::cout << secretWord << std::endl << std::endl;


}

void AddDummyWords(FWordList wordList)
{
	// Fill the set with more words
	while (game.allWords.size() < game.GetNumberOfWords())
	{
		std::string word = wordList.getRandomWord();
		game.allWords.insert(word);
	}
}

void PrintGameScreen()
{
	// Display all words
	for each (std::string word in game.allWords)
	{
		std::cout << word << std::endl;
	}
}