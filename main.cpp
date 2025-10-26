#pragma warning (disable:4996)
#include<iostream> // Include the iostream library for input and output
#include "Word.h" // Include the Word class header
#include "Line.h" // Include the "Line.h" header file
using namespace std;// Use the standard namespace

int main()
{
	int n, choice;

	// Get the number of lines in the paragraph
	cout << "Enter the number of lines in the paragraph: ";
	cin >> n;
	cout << endl;

	// Create an array of Line pointers to store each line of the paragraph
	Line** paragraph = new Line * [n];// Dynamic array of Line pointers to store each line
	for (int i = 0; i < n; ++i)
	{
		paragraph[i] = nullptr;
	}

	// Main menu loop
	do
	{
		// Display the menu
		cout << "Menu:\n\n1. Create a new line\n2. Change a line\n3. Print all lines\n4. Replace characters in all lines\n5. Add character at nth position in each line\n6. Add word at nth position in any line\n7. Delete first word from each line\n8. Reverse order of characters in any line\n9. Move words or letters in any line\n0. Exit\nEnter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1: // Create a new line for each entry in the paragraph
		{
			cin.ignore();// Ignore the newline character left in the input buffer
			for (int i = 0; i < n; i++)
			{
				string str;
				cout << "Enter a line of text: ";
				getline(cin, str); // Read a line of text including spaces
				paragraph[i] = new Line(str); // Create a new Line object and store it in the array
			}
			cout << endl;
			break;
		}
		case 2:// Change a specific line
		{
			int lineIndex;
			cout << "Enter the line number to change (1 to " << n << "): ";
			cin >> lineIndex;
			cin.ignore();
			if (lineIndex > 0 && lineIndex <= n && paragraph[lineIndex - 1] != nullptr) {
				cin >> *paragraph[lineIndex - 1]; // Overload the >> operator to read a new line into the existing Line object
			}
			else {
				cout << "Invalid line number.\n";
				cout << endl;
			}
			break;
		}
		case 3:// Print all lines
		{
			for (int i = 0; i < n; ++i) {
				if (paragraph[i] != nullptr) {
					cout << "Line " << i + 1 << ":" << *paragraph[i] << endl; // Overload the << operator to print the Line object
				}
			}
			cout << endl;
			break;
		}
		case 4:// Replace characters in all lines
		{
			for (int i = 0; i < n; ++i) {
				if (paragraph[i] != nullptr) {
					!(*paragraph[i]); // Overload the ! operator to replace characters in the Line object
				}
			}
			break;
		}
		case 5:// Add character at nth position in each line
		{
			for (int i = 0; i < n; ++i) {
				if (paragraph[i] != nullptr)
				{
					paragraph[i]->operator+=(1); // Overload the += operator to add a character at nth position in each Line object
				}
			}
			break;
		}
		case 6: // Add word at nth position in any line
		{
			int lineIndex, pos;
			string word;
			cout << "Enter the line number to add the word (1 to " << n << "): ";
			cin >> lineIndex;
			cin.ignore();

			if (lineIndex > 0 && lineIndex <= n && paragraph[lineIndex - 1] != nullptr) {
				cout << "Enter the position to add the word: (1 to " << paragraph[lineIndex - 1]->getSizeOfText() << "): ";
				cin >> pos;

				if (pos > 0 && pos <= paragraph[lineIndex - 1]->getSizeOfText())
				{
					paragraph[lineIndex - 1]->operator+=(pos); // Overload the += operator to add a word at nth position in the specified Line object
				}
				else
				{
					cout << "Invalid position number.\n";
					cout << endl;
				}
			}
			else {
				cout << "Invalid line number.\n";
				cout << endl;
			}
			break;
		}
		case 7: // Delete first word from each line
		{
			for (int i = 0; i < n; ++i) {
				if (paragraph[i] != nullptr) {
					paragraph[i]->operator-=(1); // Overload the -= operator to delete the first word from each Line object
				}
			}
			break;
		}
		case 8:// Reverse order of characters in any line
		{
			int lineIndex, wordIndex, choice;
			cout << "Enter the line number to reverse (1 to " << n << "): ";
			cin >> lineIndex;
			cin.ignore();

			if (lineIndex > 0 && lineIndex <= n && paragraph[lineIndex - 1] != nullptr)
			{
				cout << "Tap 1 to change a specific word, tap 2 to change the whole line: ";
				cin >> choice;
				if (choice == 1)
				{
					cout << "Enter the word number to reverse (1 to " << paragraph[lineIndex - 1]->getSizeOfText() << "): ";
					cin >> wordIndex;
					if (wordIndex > 0 && wordIndex <= paragraph[lineIndex - 1]->getSizeOfText())
					{
						paragraph[lineIndex - 1]->operator[](wordIndex).operator&(); // Overload the & operator to reverse the order of characters in a specific word
					}
					else
					{
						cout << "Invalid word number.\n";
						cout << endl;
					}
				}
				else if (choice == 2)
				{
					paragraph[lineIndex - 1]->operator&(); // Overload the & operator to reverse the order of characters in the whole Line object
				}
				else
				{
					cout << "Invalid number, Tap 1 to change a specific word, tap 2 to change the whole line:.\n";
					cout << endl;
				}
			}
			else
			{
				cout << "Invalid line number.\n";
				cout << endl;
			}
			break;
		}
		case 9: // Move words or letters in any line
		{
			int lineIndex, wordIndex, shiftBy, choice;
			cout << "Enter the line number to shift (1 to " << n << "): ";
			cin >> lineIndex;
			cin.ignore();

			if (lineIndex > 0 && lineIndex <= n && paragraph[lineIndex - 1] != nullptr)
			{
				cout << "Tap 1 to shift a specific word, tap 2 to shift the whole line: ";
				cin >> choice;

				if (choice == 1)
				{
					cout << "Enter the word number to shift (1 to " << paragraph[lineIndex - 1]->getSizeOfText() << "): ";
					cin >> wordIndex;
					if (wordIndex > 0 && wordIndex <= paragraph[lineIndex - 1]->getSizeOfText())
					{
						cout << "Enter the number of positions to shift: ";
						cin >> shiftBy;
						paragraph[lineIndex - 1]->operator[](wordIndex).operator>>(shiftBy);
					}
					else
					{
						cout << "Invalid word number.\n";
						cout << endl;
					}
				}
				else if (choice == 2)
				{
					cout << "Enter the number of positions to shift: ";
					cin >> shiftBy;
					paragraph[lineIndex - 1]->operator>>(shiftBy);
				}
				else
				{
					cout << "Invalid number, Tap 1 to change a specific word, tap 2 to change the whole line:.\n";
					cout << endl;
				}
			}
			else
			{
				cout << "Invalid line number.\n";
				cout << endl;
			}
			break;
		}
		default:
			cout << "Invalid choice. Please try again.\n" << endl;
			cout << endl;
			break;
		}

	} while (choice != 0);

	// Cleanup: Delete all Line objects and the paragraph array
	for (int i = 0; i < n; i++)
	{
		delete paragraph[i];
	}
	delete[] paragraph;

	return 0;
}