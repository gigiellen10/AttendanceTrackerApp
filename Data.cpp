/* File: Data.cpp
Purpose: This file contains all of the function definitions for the Data class 
Date: March 13th, 2024 */

#include "Data.hpp"

/* basic constructorso, copy constructors, getters/setters */

Data::Data(const int newRecNum, const int newID, const string& newFirstName, const string& newLastName, const string& newEmail,
	const string& newCredits, const string& newMajor, const string& newClassLevel,
	const int newNumAbsences, const Stack& newDatesAbsent)
{
	mRecordNum = newRecNum;
	mIDNum = newID;
	mFirstName = newFirstName;
	mLastName = newLastName;
	mEmail = newEmail;
	mNumCredits = newCredits;
	mMajor = newMajor;
	mClassLevel = newClassLevel;
	mNumAbsences = newNumAbsences;
	mDatesAbsent = newDatesAbsent; // overloaded copy assignment for Stack class
}

Data::Data(const Data& copyData)
{
	*this = copyData;
}

/* setters and getters */
void Data::setRecordNum(const int newRecNum)
{
	mRecordNum = newRecNum;
}

void Data::setID(const int newID)
{
	mIDNum = newID;
}

void Data::setFirstName(const string& newFirstName)
{
	mFirstName = newFirstName;
}

void Data::setLastName(const string& newLastName)
{
	mLastName = newLastName;
}

void Data::setEmail(const string& newEmail)
{
	mEmail = newEmail;
}


void Data::setCredits(const string& newCredits)
{
	mNumCredits = newCredits;
}


void Data::setMajor(const string& newMajor)
{
	mMajor = newMajor;
}


void Data::setclassLevel(const string& newClassLevel)
{
	mClassLevel = newClassLevel;
}


void Data::setNumAbsences(const int newAbsences)
{
	mNumAbsences = newAbsences;
}

void Data::setStack(const Stack& newStack)
{
	mDatesAbsent = newStack; // overloaded = operator for stack
}

int Data::getRecordNum() const
{
	return mRecordNum;
}


int Data::getID() const
{
	return mIDNum;
}


string Data::getFirstName() const
{
	return mFirstName;
}

string Data::getLastName() const
{
	return mLastName;
}

string Data::getEmail() const
{
	return mEmail;
}


string Data::getCredits() const
{
	return mNumCredits;
}


string Data::getMajor() const
{
	return mMajor;
}


string Data::getclassLevel() const
{
	return mClassLevel;
}


int Data::getNumAbsences() const
{
	return mNumAbsences;
}

Stack Data::getDatesAbsent() const
{
	return mDatesAbsent; // returns a copy of the stack
}

/*void setStack(Stack& newStack); Do we need a setter for the stack? Will it be used?...same with getter? */

/* overloaded copy assignment */
Data& Data::operator=(const Data& rhs)
{
	this->mClassLevel = rhs.mClassLevel;
	this->mIDNum = rhs.mIDNum;
	this->mMajor = rhs.mMajor;
	this->mEmail = rhs.mEmail;
	this->mNumAbsences = rhs.mNumAbsences;
	this->mRecordNum = rhs.mRecordNum;
	this->mFirstName = rhs.mFirstName;
	this->mLastName = rhs.mLastName;
	this->mNumCredits = rhs.mNumCredits;
	this->mDatesAbsent = rhs.mDatesAbsent; // overloaded copy assignment for a class Stack invoked here

	return *this;
}

/* overloaded stream insertions and extraction */
fstream& operator<<(fstream& lhs, const Data& rhs) // will allow file << Data
{
	// typecast fstream to ostream type for easily outputting std::string
	((ostream&)lhs) << rhs.getRecordNum() << "," << rhs.getID() << ",\"" << rhs.getFirstName() << "," << rhs.getLastName() << "\","
		<< rhs.getEmail() << "," << rhs.getCredits() << "," << rhs.getMajor() << "," << rhs.getclassLevel();
	
	return lhs;
}

ostream& operator<<(ostream& lhs, const Data& rhs) 
{
	// this overloaded version will allow cout << Data
	((ostream&)lhs) << rhs.getRecordNum() << "," << rhs.getID() << ",\"" << rhs.getFirstName() << "," << rhs.getLastName() << "\","
		<< rhs.getEmail() << "," << rhs.getCredits() << "," << rhs.getMajor() << "," << rhs.getclassLevel();

	return lhs;
}


