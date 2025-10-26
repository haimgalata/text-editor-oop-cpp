#pragma once // Ensure the file is included only once during compilation
#include<iostream> // Include the iostream library for input and output

using namespace std; // Use the standard namespace

class Word
{
private:
	char* word; // Pointer to a character array to store the word
	int sizeOfWord; // Size of the word

public:
	Word(const char* word, int sizeOfWord); // Constructor to initialize the word and its size
	Word(const Word& other); // Copy constructor
	~Word(); // Destructor

	Word& operator!(); // Replaces digits with their complement to 9, and letters with opposite case
	Word& operator&(); // Reverses the order of characters in the word
	Word& operator=(const Word& other); // Assignment operator
	Word& operator+=(const int n); // Adds a random character at position n
	Word& operator-=(const int n); // Deletes the character at position n	
	Word& operator>>(int n); // Circular right shift of the word by n positions
	friend istream& operator>>(istream& input, Word& w); // Input a new word
	friend ostream& operator<<(ostream& output, const Word& w); // Print the word to the screen
	
	string getName(); // Get the word as a string
	int getSize(); // Get the size of the word
};
