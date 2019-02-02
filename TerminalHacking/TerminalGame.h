#pragma once

class FWordList
{
public:

	FWordList(int wordLength); // Constructor

	std::string chooseRandomWord();

private:

	std::vector<std::string> validWords;

	bool bIsValid = false;

};

enum EDifficulty
{
	Very_Easy,
	Easy,
	Average,
	Hard,
	Very_Hard
};


// Declarations of all functions defined in 'main.cpp'
void SetupGame(EDifficulty difficulty);
void PlayGame();
void AddSecretWord(FWordList wordList);
void AddDummyWords(FWordList wordList);
void PrintGameScreen();
bool bAskToPlayAgain();

class FTerminalGame 
{
public:

	FTerminalGame(); // Constructor
	void Reset(EDifficulty difficulty);

	/// Create a set to hold the list of words to display to the player, one of them being the secret word.
	/// Sets are containers that store unique elements, guaranteeing there are no duplicate words.
	// Set containing the secret word and dummy words to be displayed to the player.
	std::set<std::string> activeWords;

	int GetWordLength();
	int GetNumberOfWords();

	EDifficulty difficulty = EDifficulty::Average;
	EDifficulty ChooseDifficulty();

	std::string secretWord;
	std::string PlayerInput;

private:

	int wordLength;
	int numberOfWords;

	std::string oneThroughFive = "12345";

};