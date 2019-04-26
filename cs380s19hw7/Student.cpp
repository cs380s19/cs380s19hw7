//*****************************************************************************
// File name:  Student.cpp
// Author:     Chris Lane 
// Date:       4/23/2017 
// Class:      CS380
// Assignment: Movies Lab
// Purpose:    To define the implementation of the student class
//*****************************************************************************

#include "Student.h"
#include <iomanip>

//*****************************************************************************
// Constructor:	Student
//
// Description: Initialize data members.
//
// Parameters:	none
//
// Returned:		none
//		
//*****************************************************************************
Student::Student ()
{
}

//*****************************************************************************
// Constructor: Student
//
// Description: Initialize data members.
//
// Parameters:  ID, name, vector of ratings
//
// Returned:	  none
//		
//*****************************************************************************
Student::Student (int ID, std::string firstName, std::string lastName)
{
	int mID = ID;
	std::string mFirstName = firstName;
	std::string mLastName = lastName;
}

//*****************************************************************************
// Destructor:	Student
//
// Description: delete data members
//
// Parameters:	none
//
// Returned:		none
//		
//*****************************************************************************
Student::~Student ()
{
}

//*****************************************************************************
// Method:			operator <<
//
// Description: Output operator
//
// Parameters:	Output Stream, Student
//
// Returned:		The Output Stream
//	
//*****************************************************************************
std::ostream& operator << (std::ostream &os, const Student &student)
{
	os << "ID: " << student.mID << " "
		<< student.mFirstName << " " << student.mLastName << std::endl;
	return os;
}

//*****************************************************************************
// Method:			operator>>
//
// Description: Input operator
//
// Parameters:	Input Stream, Student
//
// Returned:		The Input Stream
//	
//*****************************************************************************
std::istream& operator >> (std::istream &is, Student &student)
{
	is >> student.mID >> student.mFirstName >> student.mLastName;

	return is;
}

//*****************************************************************************
// Method:			computeAverage
//
// Description: Input operator
//
// Parameters:	ratings vector
//
// Returned:		average for all movies rated
//	
//*****************************************************************************
void Student::computeAverage ()
{
	double tempSum = 0;
	int count = 0;

	for (int i = 0; i < (int)mRatings.size (); i++)
	{
		if (0 != mRatings[i])
		{
			tempSum += mRatings[i];
			count += 1;
		}
	}
	mAverage = tempSum / count;
}
//*****************************************************************************
// Method:			 setRatings
//
// Description:  Set Ratings member vector
//
// Parameters:   ratings vector
//
// Returned:     none
//	
//*****************************************************************************

void Student::setRatings (std::vector<int> &ratings)
{
	mRatings = ratings;
}

//*****************************************************************************
// Method:			 setRatings
//
// Description:  Set Ratings member vector
//
// Parameters:   ratings vector
//
// Returned:     none
//	
//*****************************************************************************

double Student::getAverage () const
{
	return mAverage;
}