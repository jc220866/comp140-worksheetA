#include "stdafx.h"
#include "TerminalGame.h"

FTerminalGame::FTerminalGame() { Reset(); }

void FTerminalGame::Reset()
{
	allWords.clear();
}

int FTerminalGame::GetWordLength()
{
	return 4;
}

int FTerminalGame::GetNumberOfWords()
{
	return 10;
}
