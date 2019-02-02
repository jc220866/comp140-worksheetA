#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame game; // Initialize game

int main()
{
	do
	{
		game.difficulty = game.ChooseDifficulty();
		SetupGame(game.difficulty);
		PlayGame();
	} 
	while (bAskToPlayAgain());
	
	return 0;
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

void PlayGame()
{
	PrintGameScreen();

	// TODO: implement the rest of the game

	return;
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

void PrintGameScreen()
{
	// Display all words
	for each (std::string word in game.activeWords)
	{
		std::cout << word << std::endl;
	}
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