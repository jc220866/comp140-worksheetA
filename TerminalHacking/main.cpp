#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame game; // Initialize game

int main()
{
	PrintIntro();

	do
	{
		game.difficulty = game.ChooseDifficulty();
		SetupGame();
		PlayGame();
		PrintPostGameFeedback();
	} 
	while (bAskToPlayAgain());
	
	return 0;
}

// Prompts the player to increase the size of their cmd.exe window for optimal player experience
void PrintIntro()
{
	std::cout << "				PLEASE INCREASE THE WIDTH OF THE \
GAME WINDOW UNTIL THIS LINE FITS ON ONE LINE			" << std::endl;
	std::cout << "----------------------------------------------------------------------\
----------------------------------------------------------------------" << std::endl;
}

void SetupGame()
{
	game.Reset( game.difficulty ); // Reset the game based on the player's chosen difficulty

	/// This creates a new instance of the FWordList class
	// A list of appropriate possible words for the current word length
	FWordList wordList( game.GetWordLength() );

	AddSecretWord(wordList);
	AddDummyWords(wordList);

	// shuffle the words once so that the answer is not on top
	std::random_shuffle(game.activeWords.begin(), game.activeWords.end());
}

void AddSecretWord(FWordList wordList)
{
	// Choose secret word
	game.secretWord = wordList.chooseRandomWord();

	// Put the secret word in the set
	game.activeWords.push_back(game.secretWord);
}

void AddDummyWords(FWordList wordList)
{
	int likeness;
	std::pair<int, int> threshold = CalculateLikenessThreshold();
	std::string newWord;
	std::string ourWord;

	do 
	{
		newWord = wordList.chooseRandomWord();
		ourWord = SelectRandomGameWord();
		likeness = CompareLikeness(newWord, ourWord);

		if (game.bSuffixRule)
		{
			likeness -= CheckWordForCommonSuffixes(newWord);
		}

		if ((threshold.first <= likeness) && (likeness <= threshold.second) && bNewWordIsUnique(newWord))
		{
			game.activeWords.push_back(newWord);
		}
	}
	while ( game.activeWords.size() < game.GetNumberOfWords() );
}

std::string SelectRandomGameWord()
{
	return game.activeWords[ rand() % game.activeWords.size() ];
}

// Based on current game.wordLength, higher word lengths increase both the minimum and maximum likeness thresholds
// Returns two integers, the minimum and maximum likeness a new word can have to be added to the list.
std::pair<int, int> CalculateLikenessThreshold()
{
	int lowerPercentage = 33; // newWord must be at least XX% likeness to the current 'ourWord'
	int upperPercentage = 66; // newWord can be at most XX% likeness to the current 'ourWord'

	switch(game.difficulty)
	{
	case EDifficulty::Very_Easy:
		game.bSuffixRule = false;
		lowerPercentage = 50; 
		upperPercentage = 75;
		break;

	case EDifficulty::Easy:
		game.bSuffixRule = false;
		lowerPercentage = 33;
		upperPercentage = 66;
		break;

	case EDifficulty::Average:
		game.bSuffixRule = false;
		lowerPercentage = 33;
		upperPercentage = 50;
		break;

	case EDifficulty::Hard:
		game.bSuffixRule = true;
		lowerPercentage = 33;
		upperPercentage = 66;
		break;

	case EDifficulty::Very_Hard:
		game.bSuffixRule = true;
		lowerPercentage = 35;
		upperPercentage = 69;
		break;
	}
	int minLikeness = int( (game.GetWordLength() * lowerPercentage) / 100);
	int maxLikeness = int( (game.GetWordLength() * upperPercentage) / 100);

	return std::make_pair(minLikeness, maxLikeness);
}

// if 'ting', 'tion' or 'ally' found in the word, return 2 (to reduce likeness by 2 points).
int CheckWordForCommonSuffixes(std::string newWord)
{
	// Make sure the strings are capital letters!
	bool tion = (newWord.find("TION") != std::string::npos);
	bool ting = (newWord.find("TING") != std::string::npos);
	bool ally = (newWord.find("ALLY") != std::string::npos);

	if (tion || ting || ally)
	{
		return 2;
	}
	return 0;
}

bool bNewWordIsUnique(std::string newWord)
{
	for (auto ourWord : game.activeWords)
	{
		if (ourWord == newWord)
		{
			return false;
		}
	}
	return true;
}

void PlayGame()
{
	do 
	{
		PrintGameScreen();
		GetPlayerGuess();
		CapitalizePlayerGuess();
		CheckGuess();
		HandleGuess();
	}
	while ((game.livesLeft > 0) && (game.guessStatus != EGuessStatus::Winner));
}

void PrintGameScreen()
{

	// TODO research more about this 'for each (_ in _)' loop, it is different from and cleaner than 'std::for_each'
	// Display all words
	for each (std::string word in game.activeWords)
	{
		std::cout << word << std::endl;

		// Sleep for 50 milliseconds before printing the next word
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	std::cout << std::endl << game.playerInput << game.messageToPlayer;
	if (game.likeness >= 0) { std::cout << game.likeness; }

	std::cout << std::endl << "Lives left: " << game.livesLeft << std::endl;

	// TODO add a new lingering message for each bracket combo or valid guess, don't add a new message for each invalid guess
		// This could be accomplished by incrementing a 'line number' integer every new line
		// then having a set of previous valid messages which we add to from the bottom, pushing old ones up
		// we would have to fill it with empty space but, it could work
}

void GetPlayerGuess()
{
	std::cout << "Your guess: ";

	std::getline(std::cin, game.playerInput);

	std::cout << std::endl;
}

// Checks if the guess is in the list of words (or in the list of bracket combos)
void CheckGuess()
{
	if (bGuessStartsWithBrackets() && bGuessEndsWithBrackets())
	{
		// TODO brackets and stuff

		game.guessStatus = EGuessStatus::Bad_Brackets;
		return;
	}

	if ( game.playerInput == game.secretWord )
	{
		game.guessStatus = EGuessStatus::Winner;
		return;
	}

	for (auto word : game.activeWords) 	// Check if player's guess matches any of the valid words
	{
		if (word == game.playerInput)
		{
			game.guessStatus = EGuessStatus::OK;
			return;
		}
	}
	game.guessStatus = EGuessStatus::Invalid;
}

void CapitalizePlayerGuess()
{
	// Using auto& does not make a copy of 'c', therefore we are directly overwriting the instance's variable
	for (auto& c : game.playerInput)
	{
		c = toupper(c);
	}
}

bool bGuessStartsWithBrackets()
{
	std::string openParentheses = "(";
	std::string openSquigglies = "{";
	std::string openBrackets = "[";
	std::string openChevrons = "<";

	if ( game.playerInput.find( openParentheses ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openSquigglies ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openBrackets ) == 0 )
	{
		return true;
	}
	else if ( game.playerInput.find( openChevrons ) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool bGuessEndsWithBrackets()
{
	std::string closedParentheses = ")";
	std::string closedSquigglies = "}";
	std::string closedBrackets = "]";
	std::string closedChevrons = ">";

	if ( game.playerInput.find( closedParentheses ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedSquigglies ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedBrackets ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else if ( game.playerInput.find( closedChevrons ) == ( game.playerInput.length() - 1 ))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns likeness for a valid guess, returns a negative number otherwise
void HandleGuess()
{
	switch (game.guessStatus)
	{
	case EGuessStatus::OK:
		game.livesLeft--;
		game.messageToPlayer = ": Likeness = ";
		game.likeness = CompareLikeness(game.playerInput, game.secretWord);
		RemoveUsedWord();
		break;

	case EGuessStatus::Winner:
		// Skip guess feedback, go straight to end screen
		game.messageToPlayer = "";
		break;

	case EGuessStatus::Good_Brackets:
		game.livesLeft--;
		SubmitBrackets(); // decide whether to reset the lives or simply remove a dud
		game.likeness = -1;
		break;

	case EGuessStatus::Bad_Brackets:
		// Failed attempt at a bracket combo, take a life from the player anyway
		game.livesLeft--;
		game.messageToPlayer = ": Failed hack attempt detected, deducting life.";
		// game.messageToPlayer = ": ACCESS DENIED"; - not enough feedback?
		game.likeness = -1;
		break;

	case EGuessStatus::Invalid:
		game.messageToPlayer = ": Invalid guess. Try again.";
		game.likeness = -1;
		break;
	}
}

// Once the player has guessed a valid word, remove it from the game
void RemoveUsedWord()
{
	for (int i = 0; i < game.activeWords.size(); i++)
	{
		if (game.activeWords[i] == game.playerInput)
		{
			game.activeWords.erase( game.activeWords.begin() + i );
		}
	}
}

int CompareLikeness(std::string word, std::string word2)
{
	if (word.length() != word2.length()) { return 0; }

	int likeness = 0;

	// for every character in Guess, compare it to the secret word
	for (int i = 0; i < word.length(); i++)
	{
		// if both characters in position [i] are the same
		if (word[i] == word2[i])
		{
			// increment (add 1 to) the likeness score
			likeness++;
		}
	}
	return likeness;
}

void SubmitBrackets()
{
	// TODO: Add bracket pairs which have a 1/4 chance to reset tries, otherwise they remove a word (not the secret word) from the screen and the set

	// To get here, the player must have submitted a valid bracket and punctuation combo
	// Roll a 4 sided dice. 

	// If don't we land a 4, 
		// we remove a random word from the list of dummy words
		// RemoveDummyWord()
			// this will basically remove a word from the list, but if it's the secret word or it starts with an open bracket, don't
		// set the player message to 'Dud Removed: [REMOVED-WORD]'

		// Add the [REMOVED-WORD] to a list of removed words?
			// Have the PrintGameScreen comb through this removed words list, replacing removed words (and bracket combos) with underscores
			// TODO keep in mind that in FALLOUT, words (but not bracket combos) wrap around to the next line (even into the second section)
				// For this reason, whatever we print will have to be completely separate from what really exists
				// We will have to just print everything one character at a time (oh if only I could delay stuff by a millisecond)

	// Otherwise
		//we'll reset the player's lives back to 4.
		// set the player message to "Tries Reset."
}

void PrintPostGameFeedback()
{
	std::cout << game.playerInput << game.messageToPlayer;
	if (game.guessStatus == EGuessStatus::OK) std::cout << game.likeness;
	std::cout << std::endl;

	if (game.livesLeft > 0)
	{
		std::cout << "you the winner" << std::endl;
	}
	else
	{
		std::cout << "Lives left: " << game.livesLeft << std::endl;
		std::cout << "oof" << std::endl;
	}
}

// Uses the first letter of the player's input to determine whether they want to play another game.
bool bAskToPlayAgain()
{
	std::string playerInput = "";
	std::string FirstLetter = "default"; // FirstLetter needs to be initialized outside of the 'do' loop, any value would work here.

	do
	{
		std::cout << "Do you want to play again?" << std::endl;;
		std::getline(std::cin, playerInput);

		FirstLetter = tolower(playerInput[0]); // Changing FirstLetter to lowercase allows us to accept mixed-case "Y" and "y" as valid input
	} 
	while ((FirstLetter != "y") && (FirstLetter != "n")); // This will prompt the player to enter until they give us a Y or an N.

	return (FirstLetter == "y");  // If the player said 'yes', we return true and the game restarts. If the player said "no", the game returns false and the program closes.
}
