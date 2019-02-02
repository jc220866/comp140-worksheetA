#pragma once

class FWordList
{
public:

	FWordList(int wordLength);

	std::string getRandomWord();

private:

	std::vector<std::string> words;
};