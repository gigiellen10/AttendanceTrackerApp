/* File: Node.hpp
Purpose: This file contains the class and method definition(s) for the Node class
Date: March 13th, 2024 */

#pragma once

#include "PA7.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>

// using namespace std could replace this - bad practice!!
using std::cout;
using std::endl;
using std::cin;
using std::getline;

template <class T>
class Node
{
public:
	/* constructor - do we need copy constructor? add later */
	Node(T& newData = Data(), Node<T>* newmpNext = nullptr);

	/* setters and getters */
	void setData(const T& newData);
	void setmpNext(Node<T>* newmpNext);

	T getData(void) const;
	Node<T>* getmpNext(void) const;

	/* node utility functions */
	void editNodeAbsence();

	/* destructor */
	~Node();

private:

	T mData;
	Node<T>* mpNext;
};

/* constructor */
template <class T>
Node<T>::Node(T& newData, Node<T>* newmpNext)
{
	mData = newData; // ensure that overloaded = operator defined for type <T>
	mpNext = newmpNext; // set to nullptr by default, this is what we want 99% of the time!
}

/* setters and getters */
template <class T>
void Node<T>::setData(const T& newData)
{
	mData = newData; // need to make sure that overloaded = exists for type T, for this program will be for Data class
}


template <class T>
void Node<T>::setmpNext(Node<T>* newmpNext)
{
	mpNext = newmpNext;
}

template <class T>
T Node<T>::getData(void) const
{
	return mData;
}

template <class T>
Node<T>* Node<T>::getmpNext(void) const
{
	return mpNext;
}


/* destructor - recursive approach that leverages implicit calls of destructor for Node */
template <class T>
Node<T>::~Node()
{
	if (mpNext != nullptr)
	{
		delete mpNext;
	}
}

/* utility functions */

template <class T>
void Node<T>::editNodeAbsence()
{
	string markAbsent, currDate = getDate();
	char decision = '\0';
	Data temp(this->getData()); // need to create a temporary variable to access the member(s) of class Data we are editing

	// if not marked absent for this date already - mark the student absent (increment absent count) and add current date to stack for student
	if (temp.getDatesAbsent().isEmpty() || (temp.getDatesAbsent().peek() != currDate))
	{

		// prompt and get user selection for absence on current date
		do {
			cout << "Student #" << temp.getRecordNum() << ") " << temp.getFirstName() << ' ' << temp.getLastName()
				<< endl << "Would you like to mark this student absent for ";
			printLocalTime(); // print date (month-day-year)
			cout << "? (Y/N): ";

			getline(cin, markAbsent); // get user input

			if (!(markAbsent == "Y" || markAbsent == "N" || markAbsent == "n" || markAbsent == "y"))
			{
				// user entered invalid input, try again
				system("cls");
				cout << "Invalid input. Please enter 'Y' or 'N'" << endl;
			}

		} while (!(markAbsent == "Y" || markAbsent == "N" || markAbsent == "n" || markAbsent == "y"));


		// convert input to uppercase
		decision = toupper(markAbsent[0]);

		// increment absent count and add today's date to the stack for that student record
		if (decision == 'Y')
		{
			// increment number of absences
			temp.setNumAbsences(temp.getNumAbsences() + 1);

			// add current date to stack of absences
			Stack tempStack(temp.getDatesAbsent()); // create temp variable containing info from current node's stack
			tempStack.push(currDate); // add current date to the stack

			// insert tempStack into temporary data as updated stack
			temp.setStack(tempStack);

			// insert updated data object as new data for the node
			this->setData(temp);
		
		}
	}
	else
	{
		// student has already been marked absent for this date
		cout << "Student #" << temp.getRecordNum() << ") " << temp.getFirstName() << ' ' << temp.getLastName() << " has already been marked absent for " << currDate <<
			". Please press any key to move to the next student." << endl;
		cin.get(); //allows a pause before clearing the screen and moving to the next student
	}
	

}