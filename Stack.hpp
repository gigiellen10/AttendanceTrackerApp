/* File: Stack.hpp
Purpose: This file contains the class definition for the Stack class.
Date: March 13th, 2024 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // std::find and std::erase for vectors

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::find;


class Stack {

public:
	
	/* constructor and copy constructor */
	Stack() {};
	Stack(const Stack& copyStack);

	/* overloaded copy assignment */
	Stack& operator=(const Stack& rhs);

	/* destructor */
	~Stack() {}; // vector does not contain dynamically allocated memory, so no need to delete anything explicitly

	// pushes a std::string containing a date of absence to the stack
	void push(string& dateAbsent);

	// pops the top element off of the stack and returns the data (std::string containing a date)
	string pop(void);

	// returns the data at the top of the stack
	string peek(void);

	// prints the contents of the stack using iterators
	void printStack();

	// deletes the string searched for in the stack, if found
	bool deleteElement(string& search);

	// returns true for empty, false for not empty
	bool isEmpty(void);
	

private:
	vector<string> mVector;
};