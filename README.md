# comp140-worksheetA

"Text File Words" refers to the huge vector of words gathered from the text file
"Game Words" will refer to the small set of words chosen randomly from "Text File Words"

Current algorithm for choosing the game words:

// Randomly choose a word from the "Text File Words" vector to be the secretWord (depending on wordLength = X)
// Continue to randomly choose X long words from "Text File Words" until the "Game Words" set is full

My idea for an algorithm (in main.cpp's AddDummyWords(FWordlist wordList) function:

// Randomly choose a word from the "Text File Words" vector to be the secretWord (depending on wordLength = X)

// Until "Game Words" is full
	// Randomly select another X long word from "Text File Words", we'll call it "newWord"
		// Randomly select one of the words currently in "Game Words"*
		// Compare this selected word to the newWord, incrementing "likeness" for each letter in common
		// if "likeness" is within a certain threshold**, add it to "Game Words"
		
* The game would be too easy if every word had a large amount of likeness with the secretWord
** The likeness should not be too high, playing with "CONCENTRATION" against "CONCENTRATING" is not fun

While an alternative method could involve comparing a newWord to each word inside "Game Words", then adding it if it has a likeness to any of the "Game Words", that would require a lot of character-by-character comparison which may be arduous to compute.
However, it's worth noting that there are a lot more newWords being denied, so not only is computation time also quite high with this method, but it's entirely possible that the algorithm would fail to find enough words with likeness before reaching the end of the word file.
For that reason, it's a good idea to also:

// do
	// randomly select and compare words, adding to the "Game Words" set if of suitable length and likeness
// while the "Game Words" set is not full


EDIT:

While implementing the algorithm, I noticed an unsatisfyingly high amount of 'ing', 'tion' and 'ally' words in the higher difficulties, so I'll also implement an algorithm to reduce those words.

// if we see a tion, ing or lly in the word
	// reduce likeness by 2