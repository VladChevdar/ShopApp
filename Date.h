#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>

class Date
{
public:
	Date() : month(0), day(0), year(0) {}
	Date(int m, int d, int y); // Set date
	void display() const; // Display date

private:
	int month;
	int day;
	int year;

	bool isLeapYear(int y) const; // Return true if it's a leap year
	bool isValidDate(int m, int d, int y) const; // Return false if date is not valid
};

#endif
