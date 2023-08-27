#include "Date.h"

// Set date
Date::Date(int m, int d, int y)
{
	if(!isValidDate(m, d, y))
	{
		throw std::invalid_argument("Invalid date");
	}
	month = m;
	day = d;
	year = y;
}

// Display date MM-DD-YYYY
void Date::display() const
{
	std::cout << month << "/" << day << "/" << year << std::endl;
}

// Check if it is a leap year
bool Date::isLeapYear(int y) const
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Check if the date is valid
bool Date::isValidDate(int m, int d, int y) const
{
	if(m < 1 || m > 12) return false; // Invalid month
	if(d < 1) return false; // Negative or zero day

	// Check days based on month
	if(m == 2)
	{
		if(isLeapYear(y))
		{
			return d <= 29;
		} else {
			return d <= 28;
		}
	} else if(m == 4 || m == 6 || m == 9 || m == 11)
	{
		return d <= 30;
	} else {
		return d <= 31;
	}
}
