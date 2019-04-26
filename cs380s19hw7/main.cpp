//*****************************************************************************
// File name:  main.cpp
// Author:     Chris Lane 
// Date:       4/26/2017
// Class:      CS380
// Assignment: Movies
// Purpose:    Driver for Movie Rating System 
//*****************************************************************************

//#include <vld.h>
#include "Student.h"

#include <fstream>
#include <stdlib.h>

void printHeading ();

void printMenu ();

void printStudentAverages (std::vector<Student*> &studentVector);

void deallocateVector (std::vector<Student*> &studentVector);

void computeAverages (std::vector<Student*> &studentVector);

void processUserSelection (int userSelection,
	std::vector<Student*> &studentArray, int numStudents, int numMovies);

void populateStudents (std::vector<Student*> &studentVector, int &numMovies
	, const std::string ratingsFile, std::ifstream &inFile);

void populateRatings (std::vector<Student*> &studentVector, int &numMovies
	, const std::string ratingsFile, std::ifstream &inFile);

void populateMovies (int &numMovies, const std::string moviesFile,
	std::ifstream &inFile);

void openFileForRead (std::ifstream &inFile, const std::string fileName);

int getUserSelection (const int numChoices);

//*****************************************************************************
// Method:	    main
//
// Description: main function for movies 
//
// Parameters:  none
//
// Returned:    EXIT_SUCCESS
//	
//*****************************************************************************
int main ()
{
	const std::string STUDENTS_FILE = "students.txt";
	const std::string MOVIES_FILE = "movies.txt";
	const std::string RATINGS_FILE = "ratings.txt";

	const int NUM_CHOICES = 9;  // Number of menu choices including quit
	const int QUIT = 0;

	int numStudents; // Read in from the first line of the STUDENTS_FILE
	int numMovies;  // Read in from the first line of the MOVIES_FILE
	int userSelection;

	std::vector<Student*> studentVector;

	std::ifstream inFile;

	// Load the student info, get number of students 

	populateStudents (studentVector, numStudents, STUDENTS_FILE, inFile);

	// Get number of movies (but movie titles *not* loaded)

	populateMovies (numMovies, MOVIES_FILE, inFile);

	// Load the ratings info into studentArray

	populateRatings (studentVector, numMovies, RATINGS_FILE, inFile);

	// Populate student array with student averages for ranked movies

	computeAverages (studentVector);

	// Get user selection, process, repeat until QUIT

	userSelection = getUserSelection (NUM_CHOICES);

	while (QUIT != userSelection)
	{
		processUserSelection (userSelection, studentVector, numStudents, numMovies);
		userSelection = getUserSelection (NUM_CHOICES);
	}

	deallocateVector (studentVector);

	return EXIT_SUCCESS;
}

//*****************************************************************************
// Function:		printStudentAverages
//
// Description: Print each student ID, first name and last name in addition 
//							to their average rating for all movies they rated 
//
// Parameters:	studentVector: Vector of pointers to Students
//
// Returned:		none
//	
//*****************************************************************************
void printStudentAverages (std::vector<Student*> &studentVector)
{
	std::cout << std::endl;
	std::cout << "***Average Student Movie Ratings***"
		<< std::endl;
	for (int i = 0; i < (int)studentVector.size (); i++)
	{
		Student *pStudent = studentVector[i];
		std::cout << *pStudent << "  Average:" << pStudent->getAverage ()
			<< std::endl;
	}
}

//*****************************************************************************
// Function:		deallocateVector
//
// Description: Deallocate studentVector
//
// Parameters:	studentVector: Vector of pointers to Students
//
// Returned:		none
//	
//*****************************************************************************
void deallocateVector (std::vector<Student*> &studentVector)
{
	for (unsigned int i = 0; i < studentVector.size (); i++)
	{
		Student *pItem = studentVector[i];
		delete pItem;
		studentVector[i] = NULL;
	}
}

//*****************************************************************************
// Function:		computeAverages
//
// Description: Compute average rating for each student
//
// Parameters:	studentVector: Vector of pointers to Students
//
// Returned:    none
//	
//*****************************************************************************
void computeAverages (std::vector<Student*> &studentVector)
{
	for (unsigned int i = 0; i < studentVector.size (); i++)
	{
		Student *pStudent = studentVector[i];
		pStudent->computeAverage ();
	}
}

//*****************************************************************************
// Function:		openFile
//
// Description: Opens a input file 
//
// Parameters:	filename - name of file to open
//
// Returned:    none 
//	
//*****************************************************************************

void openFileForRead (std::ifstream &inFile, const std::string fileName)
{
	inFile.open (fileName);

	if (!inFile)
	{
		std::cout << "ERROR: Could not open" << fileName << "\n\n";
		exit (-1);
	}
}

//*****************************************************************************
// Method:			printHeading
//
// Description: clears screen, prints program heading
//
// Parameters:	none
//
// Returned:		none 
//	
//*****************************************************************************

void printHeading ()
{
	system ("CLS");
	std::cout << "**************************************************************"
		<< std::endl;
	std::cout << "                 CS 380::Movie Friend Finder" << std::endl;
	std::cout << "**************************************************************"
		<< std::endl;
}

//*****************************************************************************
// Method:			printMenu
//
// Description: prints menu of selections
//
// Parameters:	none
//
// Returned:		none 
//	
//*****************************************************************************

void printMenu ()
{
	printHeading ();
	std::cout << "Please select from the following" << std::endl;
	std::cout << "0) Quit" << std::endl;
	std::cout << "1) Print all users and overall average rating" << std::endl;
	std::cout << "2) Print all users and their movie friend and movie enemy"
		<< std::endl;
	std::cout << "3) Print pair of users that are the strongest movie friends"
		<< std::endl;
	std::cout << "4) Print pair of users that are the worst movie enemies"
		<< std::endl;
	std::cout << "5) Print movies that have the highest, lowest avg. ratings"
		<< std::endl;
	std::cout << "6) Recommend movies for users " << std::endl;
	std::cout << "7) Something else " << std::endl;
	std::cout << "8) Something something else " << std::endl;
}

//*****************************************************************************
// Method:			getUserSelection
//
// Description: Validates and returns users menu choice
//
// Parameters:	numChoices - variable that gives number of menu choices
//
// Returned:		int - userSelection
//	
//*****************************************************************************

int getUserSelection (const int numChoices)
{
	int userSelection;
	printMenu ();
	do
	{
		std::cout << "Please enter your choice: ";
		std::cin >> userSelection;

	} while (0 > userSelection || userSelection > numChoices - 1);

	return userSelection;
}

//*****************************************************************************
// Method:			populateRatings
//
// Description: populate ratings vector in student object from file 
//
// Parameters:	numMovies- number of movies
//							ratingsFile - name of ratings file
//							inFile - ifstream
//							studentVector - vector of pointers to students
// Returned:		none
//	
//*****************************************************************************

void populateRatings (std::vector<Student*> &studentVector, int &numMovies
	, const std::string ratingsFile, std::ifstream &inFile)
{
	openFileForRead (inFile, ratingsFile);

	for (int i = 0; i < (int)studentVector.size (); i++)
	{
		std::vector<int> ratings;
		int tempRating;
		Student *pStudent = studentVector[i];
		for (int i = 0; i < numMovies; i++)
		{
			inFile >> tempRating;
			ratings.push_back (tempRating);
		}
		pStudent->setRatings (ratings);
	}
	inFile.close ();
}

//*****************************************************************************
// Method:			populateStudents
//
// Description: populate ratings vector in student object from file 
//
// Parameters:	numMovies- number of movies
//							moviesFile - name of movie file
//							inFile - ifstream
//							studentVector - vector of pointers to students
//
// Returned:		none
//	
//*****************************************************************************
void populateStudents (std::vector<Student*> &studentVector, int &numStudents,
	const std::string studentsFile, std::ifstream &inFile)
{
	Student *pStudent;
	openFileForRead (inFile, studentsFile);
	inFile >> numStudents;

	for (int i = 0; i < numStudents; i++)
	{
		pStudent = new Student ();
		inFile >> *pStudent;
		studentVector.push_back (pStudent);
	}
	inFile.close ();
}

//*****************************************************************************
// Method:			populateMovies
//
// Description: populate ratings vector in student object from file 
//
// Parameters:	numMovies- number of movies
//							moviesFile - name of movie file
//							inFile - ifstream
//
// Returned:		none
//	
//*****************************************************************************

void populateMovies (int &numMovies, const std::string moviesFile,
	std::ifstream &inFile)
{
	openFileForRead (inFile, moviesFile);

	inFile >> numMovies;

	inFile.close ();
}

//*****************************************************************************
// Method:			processUserSelection

// Description: processes the user selection
//
// Parameters:	userSelection - user selection from menu
//							studentVector - vector of pointers to students
//							numStudents - number of students
//							numMovies - number of movies 
//
// Returned:		none
//	
//*****************************************************************************

void processUserSelection (int userSelection,
	std::vector<Student*> &studentVector, int numStudents, int numMovies)
{
	switch (userSelection) {
	case 1: printStudentAverages (studentVector);
		break;
	case 2: std::cout << "Case 2\n";
		break;
	case 3: std::cout << "Case 3\n";
		break;
	case 4: std::cout << "Case 4\n";
		break;
	case 5: std::cout << "Case 5\n";
		break;
	case 6: std::cout << "Case 6\n";
		break;
	case 7: std::cout << "Case 7\n";
		break;
	case 8: std::cout << "Case 8\n";
		break;
	}
	system ("pause");  // yes...I know...
}