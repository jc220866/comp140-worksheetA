#include "stdafx.h"
#include "TerminalGame.h"

int FTerminalGame::GetWordLength() { return wordLength; }
int FTerminalGame::GetNumberOfWords() { return numberOfWords; }


FTerminalGame::FTerminalGame() {  }

void FTerminalGame::Reset(EDifficulty difficulty)
{
	// Seed the random number generator with the current time,
	// This ensures secret word is different each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));

	activeWords.clear(); // empty the set containing the secret word and dummy words.

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
	// TODO random selection (coin toss?) for word length
	// TODO if lower bound of word length, choose upper bound of word count
}

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

		std::getline(std::cin, PlayerInput);
	} 
	while (oneThroughFive.find(PlayerInput) == std::string::npos); // This will prompt the player to enter until we see a number between 1 and 5.

	if (PlayerInput == "1")
	{
		return EDifficulty::Very_Easy;
	}
	else if (PlayerInput == "2")
	{
		return EDifficulty::Easy;
	}
	else if (PlayerInput == "3")
	{
		return EDifficulty::Average;
	}
	else if (PlayerInput == "4")
	{
		return EDifficulty::Hard;
	}
	else if (PlayerInput == "5")
	{
		return EDifficulty::Very_Hard;
	}

	return EDifficulty::Average;
}

int FTerminalGame::SubmitGuess(std::string playerGuess)
{
	int likeness = 0;

	// if playerGuess NOT in the list of valid guesses
		// return -1?

	for (auto Character : playerGuess)
	{
		Character = toupper(Character);
	}

	// for every character in Guess, compare it to the secret word
	for (int i = 0; i < GetWordLength(); i++)
	{
		// if both characters in position [i] are the same
		if ( toupper( playerGuess[i] ) == secretWord[i] )
		{
			// increment (add 1 to) the likeness score
			likeness++; 
		}
	}

	return likeness;
}
