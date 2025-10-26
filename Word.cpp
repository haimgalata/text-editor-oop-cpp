#pragma warning (disable:4996) // Disable specific compiler warning about deprecated functions
#include <cstdlib> // Include for standard library functions like rand
#include <cctype> // Include for character classification and conversion functions

#include "word.h" // Include the Word class header

Word::Word(const char* word, int size) // Constructor to initialize the word and its size
{
	this->word = new char[size + 1]; // Allocate memory for the word
	this->sizeOfWord = size; // Set the size of the word
	strcpy(this->word, word); // Copy the input word to the class member
	this->word[sizeOfWord] = '\0'; // Null-terminate the word
}

Word::Word(const Word& other) // Copy constructor
{
	this->sizeOfWord = other.sizeOfWord; // Copy the size of the word
	this->word = new char[sizeOfWord + 1]; // Allocate memory for the new word
	strcpy(this->word, other.word); // Copy the word from the other object
	this->word[sizeOfWord] = '\0'; // Null-terminate the word
}

Word::~Word() // Destructor
{
	delete[] word; // Free the allocated memory
}

Word& Word::operator!() // Replaces digits with their complement to 9, and letters with opposite case
{
	for (int i = 0; i < sizeOfWord; i++)
	{
		if (isdigit(word[i])) // If the character is a digit
			word[i] = '9' - (word[i] - '0'); // Replace with the complement to 9

		if (isalpha(word[i])) // If the character is a letter
		{
			if (isupper(word[i])) // If the letter is uppercase
				word[i] = tolower(word[i]); // Convert to lowercase
			else // If the letter is lowercase
				word[i] = toupper(word[i]); // Convert to uppercase
		}
	}
	return *this; // Return the modified object
}

Word& Word::operator&() // Reverses the order of characters in the word
{
	for (int i = 0, j = sizeOfWord - 1; i < j; i++, j--)
	{
		char temp = word[i]; // Swap characters from the ends towards the center
		word[i] = word[j];
		word[j] = temp;
	}
	return *this; // Return the modified object
}

Word& Word::operator=(const Word& other) // Assignment operator
{
	if (this != &other) // Check for self-assignment
	{
		delete[] word; // Free the existing memory
		word = new char[strlen(other.word) + 1]; // Allocate memory for the new word
		strcpy(word, other.word); // Copy the word from the other object
		sizeOfWord = other.sizeOfWord; // Copy the size of the word
		word[sizeOfWord] = '\0'; // Null-terminate the word
	}
	return *this; // Return the modified object
}

Word& Word::operator+=(const int n) // Adds a random character at position n
{
	if (n > 0 && n <= sizeOfWord)
	{
		char* temp = new char[sizeOfWord + 2]; // Allocate memory for the new word
		for (int i = 0; i < n - 1; i++)
		{
			temp[i] = word[i]; // Copy characters up to position n-1
		}
		temp[n - 1] = static_cast<char>('a' + (rand() % 26)); // Add a random character at position n-1

		for (int i = n; i <= sizeOfWord; i++)
		{
			temp[i] = word[i - 1]; // Copy the rest of the characters
		}
		temp[sizeOfWord + 1] = '\0'; // Null-terminate the new word

		delete[] word; // Free the old word memory
		word = temp; // Assign the new word memory to word
		sizeOfWord++; // Increment the size of the word
	}
	else
	{
		cout << "Invalid index\n" << endl; // Print an error message for an invalid index
	}

	return *this; // Return the modified object
}

Word& Word::operator-=(const int n) // Deletes the character at position n
{
	if (n >= 0 && n < sizeOfWord)
	{
		for (int i = n; i < sizeOfWord - 1; ++i)
		{
			word[i] = word[i + 1]; // Shift characters to the left from position n
		}
		word[sizeOfWord - 1] = '\0'; // Null-terminate the word
		sizeOfWord--; // Decrement the size of the word
	}
	else
	{
		cout << "Invalid index\n" << endl; // Print an error message for an invalid index
	}
	return *this; // Return the modified object
}

Word& Word::operator>>(int n) // Circular right shift of the word by n positions
{
	if (n < 0)
	{
		cout << "Invalid index\n" << endl; // Print an error message for an invalid index
		return *this;
	}
	char* temp = new char[sizeOfWord + 1]; // Allocate memory for the temporary word
	for (int i = 0; i < sizeOfWord; i++)
	{
		temp[(i + n) % sizeOfWord] = word[i]; // Perform the circular shift
	}
	temp[sizeOfWord] = '\0'; // Null-terminate the temporary word
	strcpy(word, temp); // Copy the temporary word back to word
	delete[] temp; // Free the temporary word memory

	return *this; // Return the modified object
}

istream& operator>>(istream& input, Word& w) // Input a new word
{
	cout << "Enter a new word please:\n"; // Prompt the user for input
	char temp[20]; // Temporary buffer for the input
	input >> temp; // Read the input word
	delete[] w.word; // Free the existing word memory
	w.sizeOfWord = strlen(temp); // Set the new size of the word
	w.word = new char[w.sizeOfWord + 1]; // Allocate memory for the new word
	strcpy(w.word, temp); // Copy the input word to the word member

	return input; // Return the input stream
}

ostream& operator<<(ostream& output, const Word& w) // Print the word to the screen
{
	output << w.word; // Output the word
	return output; // Return the output stream
}

string Word::getName() // Get the word as a string
{
	return this->word; // Return the word as a string
}

int Word::getSize() // Get the size of the word
{
	return sizeOfWord; // Return the size of the word
}
