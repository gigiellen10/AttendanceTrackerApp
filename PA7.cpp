/* File: PA7.cpp
Purpose: This file contains the implementations for small utility/ helper functions that are used throughout the entire program
Date: March 15th, 2024 */

#include "PA7.hpp"

// prints the date
void printLocalTime()
{
	// note: retrieved from stack overflow
	time_t t = time(0);
	struct tm* now = localtime(&t);
	cout << (now->tm_mon + 1) << '-'
		<< now->tm_mday << '-'
		<< (now->tm_year + 1900);
}

// returns a std::string containing the date
string getDate()
{
	string date;

	time_t t = time(0);
	struct tm* now = localtime(&t);
	date = to_string(now->tm_mon + 1) + '-' + to_string(now->tm_mday) + '-' + to_string(now->tm_year + 1900);

	return date;
}

void backToMenuMessage()
{
	cout << "Press any key to go back to the main menu." << endl;
	cin.get();
}

// gets user selection from main menu
int getUserSelection()
{
	int userChoice = 0;
	std::string userChoiceStr = "";

	// validate user selection and return the selection
	do {

		// clear string upon each iteration if already gotten input from user
		userChoiceStr.clear();

		cout << "Enter your selection here: ";
		cin >> userChoiceStr;

		// convert the string entered to an integer
		if (isNumeric(userChoiceStr))
		{
			userChoice = stoi(userChoiceStr);
		}
		
		if ((userChoice < 1 || userChoice > 7) && !isNumeric(userChoiceStr))
		{
			// invalid entry
			system("cls");
			cout << "That input is invalid. Please try again!" << endl;
		}

	} while ((userChoice < 1 || userChoice > 7) && !isNumeric(userChoiceStr));

	return userChoice;

}

// helper function for: editAbsences(); prompts user to select if they want to search a student by name or by ID number
// returns 1 if searching by ID num, 2 if searching by name 
int howToSearch()
{
	string decisionStr;

	do {

		cout << "Please select from the following options:\n"
			<< "1. Search student by ID number\n"
			<< "2. Search student by name\n"
			<< "Please enter your selection here: ";

		getline(cin, decisionStr);

		if (decisionStr.empty() || !(decisionStr == "1" || decisionStr == "2"))
		{
			system("cls");
			cout << "That input is invalid. Please try again." << endl;
		}

	} while (decisionStr.empty() || !(decisionStr == "1" || decisionStr == "2"));

	return stoi(decisionStr); // convert the string to an integer and return
}

// returns the string corresponding to the name or ID number of a student to be searched for
string getStudentSearchIdentifier(int IDorName)
{
	system("cls"); // clear screen before displaying messages

	string identifier;
	string nameOrID;
	bool invalid = false;

	if (IDorName == 1) // ID
	{
		nameOrID = "ID";
	}
	else // name
	{
		nameOrID = "full name";
	}

	do {
		
		// prompt for ID or name based on parameters
		cout << "Please enter the student's " << nameOrID << " you would like to search for: ";
		getline(cin, identifier);

		if (IDorName == 1 && !isNumeric(identifier)) // if we are looking for an ID, check if the string entered is numeric
		{
			invalid = true;
			system("cls");
			cout << "That input is invalid, please enter an ID number." << endl;
		}
		else
		{
			invalid = false;
		}
		

	} while (invalid); // while the string is invalid

	return identifier;
}

// returns true if string is made of numeric characters, false otherwise
bool isNumeric(string& str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (!isdigit(str[i]))
		{
			return false; // found a non-digit character in the string
		}
	}

	// if no non-digits were found, returns true by default
	return true;
}

// returns the string containing the absence to delete from the stack, from user
string getAbsenceToDelete()
{
	string date;

	cout << "Enter the absence you would like to delete from this student's record (mm-dd-yyyy): ";
	getline(cin, date);

	return date;
}
