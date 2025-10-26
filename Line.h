#pragma once // Ensure the file is included only once during compilation
#include <iostream>// Include the iostream library for input and output
#include<string> // Include the string library

using namespace std; // Use the standard namespace

#include "Word.h" // Include the Word class header

class Word; // Forward declaration of the Word class

class Line
{
private:
	string sentence; // Stores the sentence of the line
	Word** text; // Pointer to an array of Word pointers
	int sizeOfText; // Number of words in the line

public:
    int countWords(const string& str); // Counts the number of words in the string
    Line(string sentence); // Constructor to initialize the line with a sentence
    Line(const Line& other); // Copy constructor
    ~Line(); // Destructor

    Line& operator!(); // Replaces characters according to the rules specified for Word::operator!()
    Line& operator&(); // Reverses the order of characters in the line
    Line& operator=(const Line& other); // Assignment operator
    Line& operator+=(const int n); // Adds a random word at position n
    Line& operator-=(const int n); // Deletes the word at position n
    friend ostream& operator<<(ostream& output, const Line& t); // Output the line to the screen
    friend istream& operator>>(istream& input, Line& str); // Input a new line
    Line& operator>>(int n); // Circular right shift of the words in the line by n positions
    Word& operator[](int n); // Access the word at position n

    int getSizeOfText(); // Get the number of words in the line
};

