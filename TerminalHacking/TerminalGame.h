#pragma once

class FWordList
{
public:

	FWordList(int wordLength);

	std::string getRandomWord();

private:

	std::vector<std::string> words;
};

// Declarations of functions defined in 'main.cpp'
void AddSecretWord(FWordList wordList);
void AddDummyWords(FWordList wordList);
void PrintGameScreen();

class FTerminalGame 
{
public:

	FTerminalGame(); // Constructor
	void Reset();

	int GetWordLength();
	int GetNumberOfWords();

	// Create a set to hold the list of words to display to the player, one of them being the secret word.
	// Sets are containers that store unique elements, guaranteeing there are no duplicate words.
	std::set<std::string> allWords;

private:


	const int WORD_LENGTH = 5;
	const int NUMBER_OF_WORDS = 15;

};