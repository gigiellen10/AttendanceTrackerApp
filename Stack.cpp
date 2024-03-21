/* File: Stack.cpp
Purpose: This file contains all of the function definitions for the Stack class
Date: March 13th, 2024 */

#include "Stack.hpp"

/* copy constructor */

Stack::Stack(const Stack& copyStack)
{
	*this = copyStack;
}

/* overloaded copy assignment */
Stack& Stack::operator=(const Stack& rhs)
{
	this->mVector = rhs.mVector;

	return *this;
}

// pushes a std::string containing a date of absence to the stack
void Stack::push(string& dateAbsent)
{
	// inserts data at the end of the vector
	mVector.push_back(dateAbsent);
}

// pops the top element off of the stack and returns the data (std::string containing a date)
string Stack::pop(void)
{
	string deletedData;
	deletedData = this->peek();

	mVector.pop_back();

	return deletedData;
}

// returns the data at the top of the stack
string Stack::peek(void)
{
	return mVector.back();
}

// returns true for empty, false for not empty
bool Stack::isEmpty(void)
{
	return mVector.empty();
}

// prints the contents of the stack - uses iterators to access elements of stack(implemented with vector)
void Stack::printStack()
{
	cout << "Dates absent:\n";

	for (auto iterator = mVector.cbegin(); iterator != mVector.cend(); ++iterator)
	{
		// print the date contained in the vector
		cout << iterator->data() << endl;
	}

	cout << '\n';
}

// if string is successfully found and deleted, returns true; else returns false
bool Stack::deleteElement(string& search)
{
	bool success = false;
	const auto iterator = find(mVector.begin(), mVector.end(), search);

	
	if (iterator != mVector.end())
	{
		success = true; // we found the string searched for

		// delete from the vector
		mVector.erase(iterator);
	}
	
	return success;

}