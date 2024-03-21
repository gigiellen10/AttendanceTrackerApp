/* File: PA7.hpp
Purpose: This file contains the prototypes for small utility/ helper functions that are used throughout the entire program
Date: March 15th, 2024 */

#pragma once
// need for printLocalTime() function
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::getline;

void printLocalTime();
string getDate();
void backToMenuMessage();
int getUserSelection();
int howToSearch();
string getStudentSearchIdentifier(int IDorName);
bool isNumeric(string& str);
string getAbsenceToDelete();
