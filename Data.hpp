/* File: Data.hpp
Purpose: This file contains the class definition for the Data class
Date: March 13th, 2024 */

#pragma once

#include "Stack.hpp"
#include <string>

using std::string;
using std::fstream;
using std::ofstream;
using std::ostream;
using std::ifstream;


class Data
{
public:
	/* constructor and copy constructor */
	// set record number tto -1 by default - indicator that a valid record was not read in from file and should be discarded/not inserted into M List
	Data(const int newRecNum = -1, const int newID = 0, const string& newFirstName = "", const string& newLastName = "",
		const string& newEmail = "", const string& newCredits = "", const string& newMajor = "", const string& newClassLevel = "",
		const int newNumAbsences = 0, const Stack& newDatesAbsent = Stack());

	Data(const Data& copyData);

	/* setters and getters */
	void setRecordNum(const int newRecNum);
	void setID(const int newID);
	void setFirstName(const string& newFirstName);
	void setLastName(const string& newLastName);
	void setEmail(const string& newEmail);
	void setCredits(const string& newCredits);
	void setMajor(const string& newMajor);
	void setclassLevel(const string& newClassLevel);
	void setNumAbsences(const int newAbsences);
	void setStack(const Stack& newStack); 

	int getRecordNum() const;
	int getID() const;
	string getFirstName() const;
	string getLastName() const;
	string getEmail() const;
	string getCredits() const;
	string getMajor() const;
	string getclassLevel() const;
	int getNumAbsences() const;
	Stack getDatesAbsent() const;
	
	/* overloaded copy assignment */
	Data& operator=(const Data& rhs);

	/* destructor */
	~Data() {};

private:

	int mRecordNum; // record number
	int mIDNum; // student ID #
	string mFirstName; // last, first
	string mLastName;
	string mEmail; // email address
	string mNumCredits; // credits for that class or AU for audit
	string mMajor; // program of study
	string mClassLevel; // freshman, sophmore etc...

	int mNumAbsences; // stores # of absences for a student
	Stack mDatesAbsent; // stores strings representing dates the student has been absent
};

// must be able to write data to the master.csv file and the screen - 2 overloaded stream insertions
fstream& operator<<(fstream& lhs, const Data& rhs);
ostream& operator<<(ostream& lhs, const Data& rhs);
