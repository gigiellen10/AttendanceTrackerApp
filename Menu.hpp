/* File: Menu.hpp
Purpose: This file contains the class definition for the Menu class
Date: March 13th, 2024 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "List.hpp"
#include "PA7.hpp"


#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::istream;
using std::getline;

// serves as wrapper class for entire program, contains the masterList
class Menu {
public:
	Menu() {};
	~Menu() {};

	void runProgram();
	

private:

	List<Data> masterList;

	/* Menu class utility functions */
	void displayMenu();
	void displaySubMenu();
	void executeUserSelection(int userChoice);
	int getReportToBeGenerated();

	/* main operation functions */
	bool importLoadClassList(int importOrLoadMaster);
	bool storeMaster();
	bool markAbsences();
	int editAbsences();
	bool generateReport(int reportType);
	

	/* helper functions */
	void outputReportType1(ofstream& reportOutfile);
	int getMinAbsences();
	bool outputReportType2(ofstream& reportOutfile, int minAbsences);
	string getMostRecentAbsence(Node<Data>* node);
	int getStudentRecNum(Node<Data>* node);

};

string getFullStudentName(Node<Data>* node);



