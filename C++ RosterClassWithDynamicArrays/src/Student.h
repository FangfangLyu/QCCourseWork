#ifndef STUDENT
#define STUDENT

#include <string>
#include "date.h"

using std::string;

const string rank[8] ={"Lower Freshman", "Upper Freshman", "Lower Sophomore", "Upper Sophomore","Lower Junior", "Upper Junior", "Lower Senior", "Upper Senior"};
class Student{
	public:
		//constructors
		Student();
		Student(int newID, string newLname, string newFname, int newCredit, double newGPA, Date& DOB, Date& matri);
		Student(int newID, string newLname, string newFname, int newCredit, double newGPA, Date& DOB, Date& matri, string standing);


		//accessors and mutators to all private fields
		int getID() const;
		string getLastName() const;
		void setLastName(string newLname);
		string getFirstName() const;
		void setFirstName(string newFname);
		int getCredits() const;
		void setCredits(int newCredit);
		double getGPA() const;
		void setGPA(double newGPA);
		Date& getDOB();
		void setDOB(Date& newDOB);
		Date& getM_date();
		void setM_date(Date& newDate);
		string getStanding() const;
		//input and output functions
		void input();
		void output() const;
		bool operator==(const Student &other) const;
		bool operator!=(const Student &other) const;
		bool operator<(const Student &other) const;
		bool operator>(const Student &other) const;
		bool operator<=(const Student &other) const;
		bool operator>=(const Student &other) const;


		friend std::ostream& operator<<(std::ostream& out, const Student& stu);
		friend std::istream& operator>>(std::istream& in,  Student& stu);



	private:
		int IDnum;
		string lastName;
		string firstName;
		string standing;
		int credits;
		double GPA;
		Date DOB;
		Date matriculation_date;
		void setStanding();
};
#endif
