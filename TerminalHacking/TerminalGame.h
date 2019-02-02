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

enum class EDifficulty
{
	Very_Easy,
	Easy,
	Average,
	Hard,
	Very_Hard
};

enum class EGuessStatus
{
	Invalid,
	Brackets,
	OK
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

	int SubmitGuess(std::string playerGuess);

private:

	int wordLength;
	int numberOfWords;

	std::string oneThroughFive = "12345";

};

// Each word chosen needs a decent likeness score to another word
// However the likeness can't go too high, it's no fun getting a likeness score of 13 when guessing CONCENTRATION against CONCENTRATING