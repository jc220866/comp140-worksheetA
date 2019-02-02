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
void PrintIntro();
void SetupGame(EDifficulty difficulty);
void PlayGame();
void AddSecretWord(FWordList wordList);
void AddDummyWords(FWordList wordList);
void PrintGameScreen();
bool HandleGuess(std::string playerGuess);
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
	std::string GetMessageToPlayer();

	std::string secretWord;
	std::string PlayerInput;

	EDifficulty difficulty = EDifficulty::Average;
	EDifficulty ChooseDifficulty();

	EGuessStatus guessStatus = EGuessStatus::Invalid;
	EGuessStatus CheckGuess(std::string playerGuess);
	bool guessValid = false;

	void SubmitGuess();
	void SubmitBrackets();

private:

	int wordLength;
	int numberOfWords;

	// Used to select difficulty levels at the start of the game.
	std::string oneThroughFive = "12345";

	// A 'get-able' message sent to the player depending on the validity of their guess.
	std::string messageToPlayer = "Hello world!";

};

// Each word chosen needs a decent likeness score to another word
// However the likeness can't go too high, it's no fun getting a likeness score of 13 when guessing CONCENTRATION against CONCENTRATING