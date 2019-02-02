#pragma once

class FTerminalGame 
{
public:

	FTerminalGame(); // Constructor
	void Reset();

	int GetWordLength();
	int GetNumberOfWords();

private:

	

	const int WORD_LENGTH = 5;
	const int NUMBER_OF_WORDS = 15;

};