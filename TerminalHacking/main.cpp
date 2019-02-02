#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame game; // Initialize game

// TODO: Add bracket pairs which have a 1/4 chance to reset tries, otherwise they remove a word (not the secret word) from the screen and the set

int main()
{
	PrintIntro();

	do
	{
		game.difficulty = game.ChooseDifficulty();
		SetupGame(game.difficulty);
		PlayGame();
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

void SetupGame(EDifficulty difficulty)
{
	game.Reset(difficulty); // Reset the game based on the player's chosen difficulty

	/// This creates a new instance of the FWordList class
	// A list of appropriate possible words for the current word length
	FWordList wordList(game.GetWordLength());

	AddSecretWord(wordList);
	AddDummyWords(wordList);
}

void AddSecretWord(FWordList wordList)
{

	// Choose secret word
	game.secretWord = wordList.chooseRandomWord();

	// Put the secret word in the set
	game.activeWords.insert(game.secretWord);





	// Display secret word at the top of the screen
	std::cout << game.secretWord << std::endl << std::endl;
}

void AddDummyWords(FWordList wordList)
{
	// Fill the set with other random words
	while (game.activeWords.size() < game.GetNumberOfWords())
	{
		std::string word = wordList.chooseRandomWord();

		game.activeWords.insert(word);
	}
}

void PlayGame()
{
	PrintGameScreen();

	do 
	{
		std::getline( std::cin, game.PlayerInput );
		game.guessStatus = game.CheckGuess( game.PlayerInput );
		game.guessValid = HandleGuess( game.PlayerInput );
	}
	while ( ! game.guessValid );

	// TODO: implement the rest of the game

	return;
}

void PrintGameScreen()
{
	// Display all words
	for each (std::string word in game.activeWords)
	{
		std::cout << word << std::endl;

		// Sleep for 50 milliseconds before printing the next word
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	std::cout << std::endl << game.GetMessageToPlayer() << std::endl;
}

bool HandleGuess(std::string playerGuess)
{
	switch (game.guessStatus)
	{
	case EGuessStatus::OK:
		// submit guess
		return true;

	case EGuessStatus::Brackets:
		// submit brackets
		return true;

	case EGuessStatus::Invalid:
		return false;
	}
	return false;
}

// Uses the first letter of the player's input to determine whether they want to play another game.
bool bAskToPlayAgain()
{
	std::string PlayerInput = "";
	std::string FirstLetter = "default"; // FirstLetter needs to be initialized outside of the 'do' loop, any value would work here.

	do
	{
		std::cout << "Do you want to play again?" << std::endl;;

		std::getline(std::cin, PlayerInput);
		FirstLetter = tolower(PlayerInput[0]); // Changing FirstLetter to lowercase allows us to accept mixed-case "Y" and "y" as valid input.
	} 
	while ((FirstLetter != "y") && (FirstLetter != "n")); // This will prompt the player to enter until they give us a Y or an N.

	return (FirstLetter == "y");  // If the player said 'yes', we return true and the game restarts. If the player said "no", the game returns false and the program closes.
}
