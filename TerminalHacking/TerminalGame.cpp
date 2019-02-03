#include "stdafx.h"
#include "TerminalGame.h"

int FTerminalGame::GetWordLength() { return wordLength; }
int FTerminalGame::GetNumberOfWords() { return numberOfWords; }

FTerminalGame::FTerminalGame() { Reset( difficulty ); } // Constructor

// Prompts player to choose difficulty, checks valid input, returns a difficulty enum
EDifficulty FTerminalGame::ChooseDifficulty()
{
	do
	{
		std::cout << "Please select difficulty." << std::endl;;
		std::cout << "1 = Very Easy" << std::endl;;
		std::cout << "2 = Easy" << std::endl;;
		std::cout << "3 = Average" << std::endl;;
		std::cout << "4 = Hard" << std::endl;;
		std::cout << "5 = Very Hard" << std::endl;;

		std::getline(std::cin, playerInput);
	} 
	while // prompt the player to enter until we see a number between 1 and 5.
		(
			(oneThroughFive.find(playerInput) == std::string::npos)
			|| // or
			(playerInput == "")
		);

	if (playerInput == "1")
	{
		return EDifficulty::Very_Easy;
	}
	else if (playerInput == "2")
	{
		return EDifficulty::Easy;
	}
	else if (playerInput == "3")
	{
		return EDifficulty::Average;
	}
	else if (playerInput == "4")
	{
		return EDifficulty::Hard;
	}
	else if (playerInput == "5")
	{
		return EDifficulty::Very_Hard;
	}
	return EDifficulty::Average;
}

// Takes in a difficulty parameter to choose longer words for higher difficulty settings
void FTerminalGame::Reset( EDifficulty difficulty )
{
	// Seed the random number generator with the current time,
	// This ensures secret word is different each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	activeWords.clear(); // empty the set containing the secret word and dummy words.

	playerInput = "";
	messageToPlayer = "";

	constexpr int MAX_LIVES = 4;
	livesLeft = MAX_LIVES;

	// Set the word length and number of words depending on player's chosen difficulty
	switch (difficulty)
	{
	case EDifficulty::Very_Easy:
		wordLength = 4;
		numberOfWords = 10;
		break;

	case EDifficulty::Easy:
		wordLength = 6;
		numberOfWords = 12;
		break;

	case EDifficulty::Average:
		wordLength = 8;
		numberOfWords = 12;
		break;

	case EDifficulty::Hard:
		wordLength = 10;
		numberOfWords = 12;
		break;

	case EDifficulty::Very_Hard:
		wordLength = 13;
		numberOfWords = 12;
		break;
	}

	// TODO random selection for word length based on difficulty thresholds
	// TODO if lower bound of word length, choose upper bound of word count and vice versa (or average : average)
}
