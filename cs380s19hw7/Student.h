//*****************************************************************************
// File name:  Student.h
// Author:     Chris Lane
// Date:       4/25/2017
// Class:      CS380
// Assignment: Movies Lab
// Purpose:    To define the header file for an item that represents a student.
//*****************************************************************************

#ifndef _Student_H_
#define _Student_H_
#include <iostream>
#include <string>
#include <vector>

class Student
{
public:

	// constructor that sets the studentID, first name, last name
	Student (int ID, std::string firstName, std::string lastName);

	// empty constructor
	Student ();

	// destructor. 
	~Student ();

	// input and output operators
	friend std::ostream& operator << (std::ostream &os, const Student &student);
	friend std::istream& operator >> (std::istream &is, Student &student);

	// setter for the student ratings vector
	void setRatings (std::vector<int> &ratings);

	// getter for overall average
	double getAverage () const;

	// method for computing overall average rating for a student
	void computeAverage ();

private:

	int mID;
	std::string mFirstName;
	std::string mLastName;

	std::vector<int> mRatings; // vector of ratings for individual movies 
	std::vector<double> mCorrelations; // vector of correlations 

	double mAverage; // Overall average for the all the movies they have rated

	// Additional member variables for storing movie friend, movie enemy, etc.
};
#endif