#pragma warning(disable:4996) // Disable warning 4996
#include <ctime> // Include the <ctime> header for time functions
#include <sstream> // Include the <sstream> header for string streaming

#include "Line.h" // Include the "Line.h" header file

int Line::countWords(const string& str) // Define the function countWords with a string parameter and an integer return value
{
	istringstream stream(str); // Create a string stream from the input string
	string word; // Declare a string variable to store each word
	int wordCount = 0; // Initialize a variable to count words

	while (stream >> word) { // Read each word from the stream
		++wordCount; // Increment the word count
	}

	return wordCount; // Return the total word count
}

Line::Line(string sentence) // Define the constructor with a string parameter
{
	string temp = sentence + " ", currentWord = ""; // Add a space to the sentence to handle the last word, declare variables for temporary storage
	char* newWord; // Declare a pointer for a new word
	int wordSize = 0; // Initialize a variable to store the size of each word

	int size = countWords(sentence); // Call the countWords function to get the number of words in the sentence

	sizeOfText = size; // Set the sizeOfText member variable
	text = new Word * [size]; // Allocate memory for the text array
	this->sentence = sentence; // Set the sentence member variable

	for (int i = 0; i < size; ++i) // Initialize each element of text to nullptr
	{
		text[i] = nullptr;
	}

	size = 0; // Reset the size variable
	for (int i = 0; i < temp.length(); i++) // Loop through the temporary string
	{
		if (temp.at(i) != ' ') // Check if the character is not a space
		{
			currentWord += temp.at(i); // Add the character to the current word
			wordSize++; // Increment the word size
		}
		else // If a space is encountered
		{
			newWord = new char[wordSize + 1]; // Allocate memory for the new word
			strcpy(newWord, currentWord.c_str()); // Copy the current word to the new word
			newWord[wordSize] = '\0'; // Null-terminate the new word

			text[size] = new Word(newWord, wordSize); // Create a new Word object and assign it to the text array
			size++; // Move to the next position in the text array
			delete[] newWord; // Delete the temporary new word
			wordSize = 0; // Reset the word size
			currentWord = ""; // Reset the current word
		}
	}
}

Line::Line(const Line& other) // Define the copy constructor with a Line parameter
{
	sentence = other.sentence; // Copy the sentence
	sizeOfText = other.sizeOfText; // Copy the size of the text array
	text = new Word * [sizeOfText]; // Allocate memory for the text array
	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		text[i] = new Word(*other.text[i]); // Create a new Word object and assign it to the text array
	}
}

Line::~Line() // Define the destructor
{
	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		delete text[i]; // Delete the Word object
	}
	delete[] text; // Delete the text array
}

Line& Line::operator!() // Define the ! operator
{
	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		*text[i] = !(*text[i]); // Apply the ! operator to each Word object
	}
	return *this; // Return a reference to the modified Line object
}

Line& Line::operator&() // Define the & operator
{
	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		text[i]->operator&(); // Apply the & operator to each Word object
	}
	return *this; // Return a reference to the modified Line object
}

Line& Line::operator=(const Line& other) // Define the assignment operator
{
	if (this == &other) { // Check for self-assignment
		return *this; // Return the current object if self-assignment is detected
	}

	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		delete text[i]; // Delete the existing Word objects
	}
	delete[] text; // Delete the text array

	sentence = other.sentence; // Copy the sentence
	sizeOfText = other.sizeOfText; // Copy the size of the text array

	text = new Word * [sizeOfText]; // Allocate memory for the text array
	for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
	{
		text[i] = new Word(*other.text[i]); // Create a new Word object and assign it to the text array
	}

	return *this; // Return a reference to the modified Line object
}

Line& Line::operator+=(const int n) // Define the += operator
{
	Word** temp = new Word * [sizeOfText + 1]; // Allocate memory for a new text array with one extra element

	for (int i = 0; i < n - 1; i++) // Copy elements up to position n-1
	{
		temp[i] = text[i];
	}

	for (int i = n - 1; i < sizeOfText; i++) // Shift elements from position n to the end
	{
		temp[i + 1] = text[i];
	}

	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
	int randomNumber = rand() % 10 + 1; // Generate a random number between 1 and 10
	char* newWord = new char[randomNumber + 1]; // Allocate memory for a new random word
	newWord[randomNumber] = '\0'; // Null-terminate the new word

	for (int i = 0; i < randomNumber; i++) // Generate a random lowercase letter for each position in the new word
	{
		newWord[i] = 'a' + rand() % 26;
	}
	newWord[randomNumber] = '\0'; // Null-terminate the new word

	temp[n - 1] = new Word(newWord, randomNumber); // Create a new Word object and assign it to position n-1

	delete[] newWord; // Delete the temporary new word
	delete[] text; // Delete the old text array
	sizeOfText++; // Increment the size of the text array
	text = temp; // Assign the new text array

	return *this; // Return a reference to the modified Line object
}

Line& Line::operator-=(const int n) // Define the -= operator
{
	if (n <= 0 || n > sizeOfText) // Check if the index is valid
	{
		cout << "Invalid index\n" << endl; // Output an error message
		return *this; // Return the current object
	}
	delete text[n - 1]; // Delete the Word object at the specified index
	for (int i = n - 1; i < sizeOfText; i++) // Shift the elements after the deleted element
	{
		text[i] = text[i + 1];
	}
	text[sizeOfText - 1] = nullptr; // Set the last element to nullptr
	--sizeOfText; // Decrement the size of the text array

	return *this; // Return a reference to the modified Line object
}

ostream& operator<<(ostream& output, const Line& t) // Define the << operator
{
	string temp; // Declare a temporary string
	for (int i = 0; i < t.sizeOfText; i++) // Loop through each element of the text array
	{
		temp += t.text[i]->getName() + " "; // Append each word to the temporary string
	}
	output << temp; // Output the temporary string
	return output; // Return the output stream
}

istream& operator>>(istream& input, Line& str) // Define the >> operator
{
	string newSentence; // Declare a string to store the new sentence

	for (int i = 0; i < str.sizeOfText; i++) // Loop through each element of the text array
	{
		delete str.text[i]; // Delete the existing Word objects
	}
	delete[] str.text; // Delete the text array

	cout << "Enter a line of text: "; // Prompt the user for input
	getline(input, newSentence); // Read a line of text from the input

	str.sentence = newSentence; // Set the sentence member variable
	str.sizeOfText = str.countWords(newSentence); // Count the number of words in the new sentence
	str.text = new Word * [str.sizeOfText]; // Allocate memory for the text array
	std::string temp = newSentence + " ", currentWord = ""; // Add a space to handle the last word
	int wordSize = 0, size = 0;

	for (int i = 0; i < temp.length(); i++) // Loop through the temporary string
	{
		if (temp.at(i) != ' ') // If the current character is not a space
		{
			currentWord += temp.at(i); // Add the character to the current word
			wordSize++; // Increment the word size
		}
		else // If a space is encountered
		{
			char* newWord = new char[wordSize + 1]; // Allocate memory for the new word
			std::strcpy(newWord, currentWord.c_str()); // Copy the current word to the new word
			newWord[wordSize] = '\0'; // Null-terminate the new word

			str.text[size] = new Word(newWord, wordSize); // Create a new Word object and assign it to the text array
			size++; // Move to the next position in the text array
			delete[] newWord; // Delete the temporary new word
			wordSize = 0; // Reset the word size
			currentWord = ""; // Reset the current word
		}
	}

	return input; // Return the input stream
}

Line& Line::operator>>(int n) // Define the >> operator with an integer parameter
{
	if (n < 0) // Check if the index is valid
	{
		cout << "Invalid index\n" << endl; // Output an error message
	}
	else
	{
		Word** temp = new Word * [sizeOfText]; // Allocate memory for a new text array
		for (int i = 0; i < sizeOfText; i++) // Loop through each element of the text array
		{
			temp[(i + n) % sizeOfText] = text[i]; // Shift elements circularly by n positions
		}

		delete[] text; // Delete the old text array

		text = temp; // Assign the new text array

		return *this; // Return a reference to the modified Line object
	}
}

Word& Line::operator[](int n) // Define the [] operator with an integer parameter
{
	if (n <= 0 || n > sizeOfText) // Check if the index is valid
	{
		cout << "Invalid index\n" << endl; // Output an error message
	}
	return *text[n - 1]; // Return a reference to the Word object at the specified index
}

int Line::getSizeOfText() // Define the getSizeOfText function
{
	return sizeOfText; // Return the size of the text array
}
