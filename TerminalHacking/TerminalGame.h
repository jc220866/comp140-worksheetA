#pragma once

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
	OK,
	Invalid,
	Winner,
	Wrong_Length,
	Good_Brackets,
	Bad_Brackets
};

class FWordList
{
public:

	FWordList(int wordLength); // Constructor

	std::string chooseRandomWord();

private:

	std::vector<std::string> validWords;

	bool bIsValid = false;

};

// Declarations of all functions defined in 'main.cpp'
void PrintIntro();
void SetupGame();
void AddSecretWord(FWordList wordList);
void AddDummyWords(FWordList wordList);
std::string SelectRandomGameWord();
std::pair<int, int> CalculateLikenessThreshold();
int CheckWordForCommonSuffixes(std::string newWord);
bool bNewWordIsUnique(std::string newWord);
void PlayGame();
void PrintGameScreen();
void GetPlayerGuess();
void CheckGuess();
void CapitalizePlayerGuess();
bool bGuessStartsWithBrackets();
bool bGuessEndsWithBrackets();
void HandleGuess();
int CompareLikeness(std::string word, std::string word2);
void SubmitBrackets();
void PrintPostGameFeedback();
bool bAskToPlayAgain();

class FTerminalGame 
{
public:

	FTerminalGame(); // Constructor
	void Reset( EDifficulty difficulty );

	// Reduces amount of 'ing', 'tion' and 'ally' words in higher difficulties
	bool bSuffixRule;

	std::string secretWord;

	/// Create an unordered set to hold the list of words to display to the player, one of them being the secret word.
	/// Unordered_ets are containers that store unique elements, guaranteeing there are no duplicate words.
	/// Being unordered, they are a little faster than standard sets, plus we 
	// Unordered set containing the secret word and dummy words to be displayed to the player.
	std::vector<std::string> activeWords;

	int GetWordLength();
	int GetNumberOfWords();

	int likeness = -1;
	int livesLeft;

	std::string playerInput;

	// Defaulted to 'Average'
	EDifficulty difficulty = EDifficulty::Average;
	EDifficulty ChooseDifficulty();

	EGuessStatus guessStatus = EGuessStatus::Invalid;
	
	std::string messageToPlayer = "";

private:

	int wordLength;
	int numberOfWords;

	// Used to select difficulty levels at the start of the game.
	std::string oneThroughFive = "12345";

};

// TODO Algorithm 3: Each word chosen needs a decent likeness score to another word
// However the likeness can't go too high, it's no fun getting a likeness score of 13 when guessing CONCENTRATION against CONCENTRATING
