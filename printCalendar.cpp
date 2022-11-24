// Function to print the calendar
#include<bits/stdc++.h>
#include "printCalendar.h"

using namespace std;

/*A Function that returns the index of the day
of the date- day/month/year

Index	 Day
0		 Sunday
1		 Monday
2		 Tuesday
3		 Wednesday
4		 Thursday
5		 Friday
6		 Saturday
*/
int dayNumber(int day, int month, int year)
{

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;

	return ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}


/* Month Number Index
0		January
1		February
2		March
3		April
4		May
5		June
6		July
7		August
8		September
9		October
10		November
11		December    */

string getMonthName(int monthNumber){
	string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	return (months[monthNumber]);
}


// Return the number of days in a month
int numberOfDays (int monthNumber, int year){
	// January, March, May, July, October, December
	if (monthNumber == 0 || monthNumber == 2 || monthNumber == 4 || monthNumber == 6 || monthNumber == 7 || monthNumber == 9 || monthNumber == 11)
		return (31);

	// April, June, September, November
	if (monthNumber == 3 || monthNumber == 5 || monthNumber == 8 || monthNumber == 10)
		return (30);

	// February
	if (monthNumber == 1)
	{
		// if leap year
		if (year % 400 == 0 ||
				(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}
	else cout<< "Invalid month";
	    return 0;
}

// Function to print the calendar of the given year
void printCalendar(int year){

	int monthNumber, days, i;

	cout << "\n\nEnter year: ";
	cin >> year;
	cout << "\n";

	cout << "Enter month number (1-12): ";
	cin >> monthNumber;
	cout << "\n";

	cout << "	Year: " << year << "\n";  //print year

	monthNumber -= 1; //adjust month number

	days = numberOfDays (monthNumber, year);

	// Print the month name
	cout << "------------"<<getMonthName (monthNumber).c_str() << "------------\n";
	cout << "number of days: "<< numberOfDays(monthNumber, year)<< "\n";

		// Print the columns
	cout << " Sun Mon Tue Wed Thu Fri Sat\n";

    int current = dayNumber (1, monthNumber+1, year);   // Index of the day from 0 to 6

	// Print appropriate spaces
	for (i = 0; i < current; i++) cout << "     ";     //spacing still needs to be fixed

	for (int j = 1; j <= days; j++){
		cout << " " << j << "  ";

		if (++i > 6){
			i = 0;
			cout << "\n";
			}
	}

	if (i)
	cout << "\n";

	current = i;

	return;
}

/*
int main()
{
	int year;

	printCalendar(year);

	return (0);
}
*/
