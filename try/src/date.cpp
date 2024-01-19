#include "date.h"
#include <iostream>
using namespace std;

// Initializes a date to the default value of January 1, 1970
Date::Date() {
   month = 1;
   day = 1;
   year = 1970;
}

// Initializes a date to the values in the parameters.  If the
// date is not legal, sets the date to 1 of the illegal value.
// (Illegal years are set to 2000)
Date::Date(int m, int d, int y) {
   month = m;
   day = d;
   year = y;
   adjust();
}
Date::Date(const Date& other): month(other.month), day(other.day), year(other.year){
	//empty;
}
Date& Date::operator=(const Date& other){
	//=
	month = other.month;
	day = other.day;
	year = other.year;
	return *this;
}

// Returns the month stored by the class
string Date::getMonth() const {
   if (month == 1)
      return "January";
   if (month == 2)
      return "February";
   if (month == 3)
      return "March";
   if (month == 4)
      return "April";
   if (month == 5)
      return "May";
   if (month == 6)
      return "June";
   if (month == 7)
      return "July";
   if (month == 8)
      return "August";
   if (month == 9)
      return "September";
   if (month == 10)
      return "October";
   if (month == 11)
      return "November";
   return "December";
}

// Returns the month stored by the class as a number
int Date::getMonthNum() const { return month; }

// Returns the day stored by the class
int Date::getDay() const { return day;}

// Retruns the year stored by the class
int Date::getYear() const { return year;}


// solicit the date from the user
void Date::input()
{
   cout << "Input month: ";
   cin >> month;
   cout << "Input day: ";
   cin >> day;
   cout << "Input year: ";
   cin >> year;
   adjust();
}

// output the date in a nice format
void Date::output() const
{
   cout << "Date: " << getMonth() << " " << day << ", " << year << endl;
}


// Fixes the date so that it is in legal range
void Date::adjust() {
   if (month < 1)
      month = 1;
   if (month > 12)
      month = 12;
   if (day < 1)
      day = 1;
   if (day > 31)
      day = 31;
   if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) &&
       (day > 30))
      day = 30;
   if ((month == 2) && (year % 4 != 0) && (day > 28))
      day = 28;
   if ((month == 2) && (year % 4 == 0) && (day > 29))
      day = 29;
}

void Date::setMonthNum(int m){
	month = m;
}
void Date::setDayNum(int d){
	month = d;
}
void Date::setYearNum(int y){
	month = y;
}

//friend
std::ostream& operator<<(std::ostream& out, const Date& d){
	out << d.month << "/" << d.day << "/" << d.year;
	return out;
}

std::istream& operator>>(std::istream& in, Date& d){
	std::cout << "A date must be in the form (month, day, year): " << std::endl;
	int month,day, year;
	char ch;
	in >> ch;
	if(ch != '('){
		std::cout << "Error: must start with '('" << std::endl;
		exit(1);
	}
	in >> month;
	in >> ch;
	if(ch!=','){
		std::cout << "Error: comma must come after real part" << std::endl;
		exit(1);
	}
	in >> day;
	in >> ch;
	if(ch!=','){
		std::cout << "Error: comma must come after real part" << std::endl;
		exit(1);
	}
	in >> year;
	in >> ch;
	if(ch != ')'){
		std::cout << "Error: must end with ')'" << std::endl;
		exit(1);
	}
	/*d.setMonthNum(month);
	d.setDayNum(day);
	d.setYearNum(year);*/
	d.month = month;
	d.day = day;
	d.year = year;
	d.adjust();


	return in;
}

std::string Date::toString() const {
    return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
}

