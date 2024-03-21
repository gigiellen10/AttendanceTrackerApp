/* File: Menu.cpp
Purpose: This file contains the function definitions for the Menu class
Date: March 13th, 2024 */

#include "Menu.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

// main program function, simulates program in main()
void Menu::runProgram()
{
	int userChoice = 0;

	cout << "Welcome to your Class Attendance Tracker! Please select from the menu below." << endl;

	while (userChoice != 7) // choice 7 selected to exit main menu loop
	{
		displayMenu();
		userChoice = getUserSelection();
		executeUserSelection(userChoice);
	}
	

}

// displays main menu for initial options
void Menu::displayMenu()
{
	
	cout << "1. Import course list\n"
		<< "2. Load master list\n"
		<< "3. Store master list\n"
		<< "4. Mark absences\n"
		<< "5. Edit absences\n"
		<< "6. Generate report\n"
		<< "7. Exit" << endl;
}

// if option 6 of main menu selected, this menu will be displayed
void Menu::displaySubMenu()
{
	system("cls");
	cout << "Please select from the following options:\n"
		<< "1. Generate report for all students\n"
		<< "2. Generate report for students with 'n' or more absences\n"
		<< "Enter your selection here: ";
}

// main switch statement that executes the operations from the main menu
void Menu::executeUserSelection(int userChoice)
{

	bool success = false;
	int reportType = 0,
		resultDeleteSearch = 0;

	switch (userChoice)
	{
	case 1:

		success = this->importLoadClassList(1); // import records from classList.csv
		system("cls");
		if (success)
		{
			cout << "Records from classList.csv sucessfully loaded into Master List!" << endl;
		}

		break;
	case 2:
		success = this->importLoadClassList(2);
		system("cls");
		if (success)
		{
			cout << "Records from master.csv sucessfully loaded into Master List!" << endl;
		}

		break;
	case 3:
		system("cls");
		success = this->storeMaster(); // store existing Master records to master.csv
		if (success)
		{
			cout << "Records from the Master List were sucessfully loaded into master.csv!" << endl;
		}

		break;
	case 4:
		system("cls");
		success = this->markAbsences();
		if (success)
		{
			cout << "You've reached the end of the master list. Absences for ";
			printLocalTime();
			cout << " have been updated." << endl;
		}

		break;
	case 5:
		
		system("cls");
		
		// if master list is emtpy, cannot edit any absences
		if (masterList.isEmpty())
		{
			cin.ignore(); // ignore newline left in stream
			cout << "The master list is empty. There are currently no students absences to delete/modify." << endl;

		}
		else
		{
			resultDeleteSearch = editAbsences(); // edit absences

			if (resultDeleteSearch == 1) // did not find student
			{
				cout << "The student you searched for was not found in the list. Go back to the main menu to try again." << endl;
			}
			else if (resultDeleteSearch == 2) // found student but not absence date
			{
				cout << "The student searched for was found, but the absence date was not located in the records." << endl;
			}
			else if (resultDeleteSearch == 3) // success
			{
				cout << "The records for the student were found and the date was successfully deleted from the log of absences." << endl;
			}

		}

		backToMenuMessage();
		system("cls");

		break;
	case 6:
		
		system("cls");
		// if master list is emtpy, cannot generate reports
		if (masterList.isEmpty())
		{
			cin.ignore(); // ignore newline in stream before getting input
			cout << "The master list is empty. No attendance reports could be outputted to absenceReport.txt!" << endl;
			
		}
		else
		{
			cin.ignore(); // ignore last character in stream before getting input, \n
			reportType = this->getReportToBeGenerated();
			system("cls");
			success = this->generateReport(reportType);

			if (success)
			{
				cout << "Your absence report has been outputted to absenceReport.txt!!" << endl;
			}
			else
			{
				cout << "No report was outputted to the file. Either the file could not be opened or no records matched the parameters entered." << endl;
			}
		}

		backToMenuMessage();
		system("cls");
		
		break;
	case 7:
		
		// exit program - store existing list to master.csv file and exit program
		this->storeMaster();
		system("cls");
		cout << "Exiting program...goodbye!" << endl;
		break;
	}

}


// carries out import class list function or load master list function - pass in 1 for import(), 2 for loadMaster()
bool Menu::importLoadClassList(int importOrLoadMaster)
{
	ifstream infile;
	std::string tempLine;
	bool success = false;

	if (importOrLoadMaster == 1)
	{
		infile.open("classList.csv");
	}
	else
	{
		// open the master.csv file
		infile.open("master.csv");
	}

	
	// if file opened successfully
	if (infile.is_open())
	{
		success = true;

		// overwrite master list completely by destroying any existing nodes
		if (!masterList.isEmpty())
		{
			masterList.~List(); 
		}

		// ignore and discard the first line - will be labels for classList or heading for master.csv
		if (!infile.eof())
		{
			getline(infile, tempLine);
		}

		while (!infile.eof())
		{
			Data tempData;

			// read and parse lines until the end of the file is reached - check that tempLine is not empty string, stoi() will throw exeption otherwise
			getline(infile, tempLine, ',');
			if (!tempLine.empty())
			{
				tempData.setRecordNum(stoi(tempLine));
			}
			getline(infile, tempLine, ',');
			if (!tempLine.empty())
			{
				tempData.setID(stoi(tempLine));
			}
			getline(infile, tempLine, '"'); // get rid of quote on left side of name
			getline(infile, tempLine, ',');
			tempData.setLastName(tempLine);
			getline(infile, tempLine, '"');
			tempData.setFirstName(tempLine);
			getline(infile, tempLine, ','); // get rid of comma after end quote on right side of last name
			getline(infile, tempLine, ',');
			tempData.setEmail(tempLine);
			getline(infile, tempLine, ',');
			tempData.setCredits(tempLine);
			getline(infile, tempLine, ',');
			tempData.setMajor(tempLine);
			getline(infile, tempLine, '\n');
			tempData.setclassLevel(tempLine);

			// insert new record into master list if not an empty record
			if (tempData.getRecordNum() != -1)
			{
				masterList.insertAtFront(tempData);
			}
			
		}

		infile.close();
	}
	else
	{
		cout << "The file could not be opened! No records were loaded to the Master List." << endl;
	}

	return success;
}

// stores the contents of the current list into master.csv; returns true if the list was not empty and the contents were stored
bool Menu::storeMaster()
{
	bool success = false;
	ofstream masterOutfile;
	Node<Data>* iterate = masterList.getmpHead(); // set a temporary node ptr to start of current master list

	if (!masterList.isEmpty())
	{
		// open file and write contents of Master List to file in correct format
		success = true;
		masterOutfile.open("master.csv");
		if (masterOutfile.is_open())
		{
			// while we are not at the end of the master linked list
			masterOutfile << "*** Master List ***" << endl; // output header for master list file

			while (iterate != nullptr)
			{
				masterOutfile << iterate->getData() << endl; // overloaded stream insertion operator
				iterate = iterate->getmpNext();
			}
			masterOutfile.close();
		}
	}
	else
	{
		cout << "The Master List did not contain any data. No records were outputted to master.csv" << endl;
	}

	return success;

}

// allows students to be marked absent, increments absent count and adds date to the stack if haven't tallied absences for that day
bool Menu::markAbsences()
{
	bool success = false;
	Node<Data>* iterateList = masterList.getmpHead(); // set a temp ptr to start of master list to visit each node

	// if master list is not empty, loop through and edit absences
	if (!masterList.isEmpty())
	{
		success = true;
		cin.ignore(); // ignore last character in stream before attempting to get input, \n
		while (iterateList != nullptr)
		{
			system("cls");
			iterateList->editNodeAbsence();

			// update ptr to next node in list
			iterateList = iterateList->getmpNext();

		}
		system("cls"); // clear screen after displaying all students
	}
	else
	{
		cout << "The Master List is empty. No records are available to update absences." << endl;
	}

	return success;
}


// allows absences for dates to be removed if they were found to be present after being marked absent
int Menu::editAbsences()
{
	cin.ignore(); // ignore newline in stream before getting input

	bool success = false; // indicates if we found student searched for and edited successfully
	int searchType = howToSearch(), // determines if we are searching for an ID or a name
		ID = -1, // will use to search by ID
		resultSearchDelete = 3; // will return to indicate if student was found, if absence date was found, if successful deletion
	
	string studentName, absenceToDelete; // will use to search by name

	Node<Data>* target; // will use to find and edit absences of target student

	Data temp; // will use to access data within node; since node/list is template, cannot access data methods directly

	Stack tempStack; // will use to access stack within data contained in node, for same reason as above

	if (searchType == 1)
	{
		
		ID = stoi(getStudentSearchIdentifier(1)); // get the ID to search for - convert the string returned into an integer
		target = masterList.searchList(ID); // search for the corresponding ID, find node located at if exists

	}
	else
	{
		studentName = getStudentSearchIdentifier(2); // get the student name to search for
		target = masterList.searchList(studentName); // search for student name, find and return node if exists

	}

	if (target != nullptr)
	{
		// we found the student that was searched for, prompt and edit absence - new function
		resultSearchDelete = 2; // found correct student node, haven't searched for absence yet
		system("cls");
		temp = target->getData(); // we need a temp data variable to access it's methods
		tempStack = temp.getDatesAbsent(); // need a secondary temp variable to access print stack
		
		if (tempStack.isEmpty())
		{
			resultSearchDelete = 4; // indicates the student was found but no absences were logged
			cout << "Oops! There are no absences on record for that student. None are available to be modified." << endl;
		}
		else
		{
			tempStack.printStack(); // print items in stack to the screen
			absenceToDelete = getAbsenceToDelete(); 
			system("cls"); 
			success = tempStack.deleteElement(absenceToDelete); // delete element from the temporary stack

			temp.setNumAbsences(temp.getNumAbsences() - 1); // decrease number of absences
			temp.setStack(tempStack); // add updated stack
			target->setData(temp); // inserted updated data back into current node
			
			if (success)
			{
				resultSearchDelete = 3; // found student, found absence string and successfully deleted
			}
		}
		
	}

	return resultSearchDelete;


}

// helper function to outputReportType2(): gets and validates min number of absences for a student to be displayed for report 2
int Menu::getMinAbsences()
{
	int minAbsences = -1;
	string minStr;

	do
	{
		cout << "Enter the minimum number of absences to filter your absence report by: ";
		getline(cin, minStr);


		if (!minStr.empty())
		{
			minAbsences = stoi(minStr); // check if minStr is empty before using stoi(); will throw an exeption
		}
		
		if (minAbsences < 0 || minStr.empty())
		{
			system("cls");
			cout << "That input is invalid. Please try again" << endl;
		}
		
	} while (minAbsences < 0 || minStr.empty());

	return minAbsences;

}

// outputs a report detailing the student name and the last reported absence of that student
bool Menu::outputReportType2(ofstream& reportOutfile, int minAbsences)
{
	Node<Data>* iterateMList = masterList.getmpHead(); // will use to visit each node in master list
	string studentName;
	Data temp; // use this to temporarily access & print data in the node, get number of absences, etc.
	int numAbsences = -1, IDNum = 0;
	bool success = false;

	while (iterateMList != nullptr)
	{
		studentName = getFullStudentName(iterateMList);
		temp = iterateMList->getData();
		IDNum = this->getStudentRecNum(iterateMList); // get record number of student to output
		numAbsences = temp.getNumAbsences();
		

		// if the student's absences matches or exceeds the min # passed in, include in report
		if (numAbsences >= minAbsences)
		{
			success = true; // we found and outputted at least one student matching the search parameters
			reportOutfile << "Student #" << IDNum << ": " << studentName
				<< ", # absences: " << numAbsences << endl;
		}
		
		iterateMList = iterateMList->getmpNext();
	}

	return success;
}

// outputs a report detailing the student name and the last reported absence of that student
void Menu::outputReportType1(ofstream& reportOutfile)
{
	Node<Data>* iterateMList = masterList.getmpHead(); // will use to visit each node in master list
	string dateAbsent, studentName; // dateAbsent will contain std::string with date last absent for a node
	int IDNum = 0;

	while (iterateMList != nullptr)
	{
		dateAbsent = this->getMostRecentAbsence(iterateMList); // get most recent absence of student
		studentName = getFullStudentName(iterateMList); // get name of student to output
		IDNum = this->getStudentRecNum(iterateMList); // get record number of student to output

		reportOutfile << "Student #" << IDNum << ": " << studentName;

		// if stack was not empty, output student name and last date absent
		if (dateAbsent != "")
		{
			reportOutfile << ", Date Last Absent: " << dateAbsent << endl;
		}
		else
		{
			// indicate that student had no recent absences
			reportOutfile << ", No recent absences found." << dateAbsent << endl;
		}

		iterateMList = iterateMList->getmpNext();
	}
}


// only called if list is not empty, outputs the report requested to absenceReport.txt
bool Menu::generateReport(int reportType)
{
	bool success = false; // indicates  if report was outputted to the file
	ofstream reportOutfile;
	int minAbsences = -1;
	

	reportOutfile.open("absenceReport.txt");
	
	if (reportOutfile.is_open()) // if file was opened successfully
	{
		

		// if the master list is empty, output message to file
		if (reportType == 1)
		{
			this->outputReportType1(reportOutfile);
			success = true; // successfully outputted requested report
		}
		else 
		{
			// reportType = 2
			minAbsences = this->getMinAbsences();
			system("cls");
			success = this->outputReportType2(reportOutfile, minAbsences);

		}

		reportOutfile.close();
	}


	return success;
}

// displays submenu and gets user input for type of report they want generated
int Menu::getReportToBeGenerated()
{
	string decisionStr;
	bool invalid = false; // will indicate if input is invalid (not = 1 or not = 2)
	int decision = 0;

	// display submenu, get input, validate input
	do {

		displaySubMenu();
		getline(cin, decisionStr);

		if (decisionStr.empty() || !(decisionStr == "1" || decisionStr == "2")) // if string is empty and does not contain 1 or 2
		{
			invalid = true;
			system("cls");
			cout << "That input is invalid. Please press any key to continue and try again." << endl;
			cin.get();

		}
		else
		{
			decision = stoi(decisionStr);
			invalid = false;
		}

	} while (invalid);

	return decision;
}

// returns most recent absence of student contained in node
string Menu::getMostRecentAbsence(Node<Data>* node)
{
	// this is how we will temporarily access the data contained in node
	Data tempData = node->getData();

	// if the stack containing absences is not empty
	if (!tempData.getDatesAbsent().isEmpty())
	{
		return tempData.getDatesAbsent().peek();
	}
	else
	{
		// stack is empty, return an empty string
		return "";
	}
	
}

// returns full name of student contained in a node 
string getFullStudentName(Node<Data>* node)
{
	Data tempData = node->getData();
	string fullName;

	// string together first and last name contained in node
	fullName = tempData.getFirstName() + ' ' + tempData.getLastName();

	return fullName;
}

// returns the record number contained in a node
int Menu::getStudentRecNum(Node<Data>* node)
{
	Data tempData = node->getData();

	return tempData.getRecordNum();
}


