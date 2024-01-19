#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
   public:
      // Initializes a date to the default value of January 1, 1970.
      Date();

      // Initializes a date to the values in the parameters.  If the
      // date is not legal, sets the date to one of the legal values.
      Date(int m, int d, int y);

      // Returns the month stored by the class
      std::string getMonth() const;
      Date(const Date& other);
      Date& operator=(const Date& other);

      // Returns the month stored by the class as a number
      int getMonthNum() const;
      void setMonthNum(int m);
      // Returns the day stored by the class
      int getDay() const;
      void setDayNum(int d);

      // Returns the year stored by the class
      int getYear() const;
      void setYearNum(int y);

      // solicit the date from the user
      void input();

      // output the date in a nice format
      void output() const;
      friend std::ostream& operator<< (std::ostream& , const Date& );
      friend std::istream& operator>>(std::istream& , Date& );

      std::string toString() const;
      friend std::string operator+(const std::string& str, const Date& date) {
              return str + date.toString();
      }
   private:
      int month, day, year;
	  void adjust();
};

#endif
