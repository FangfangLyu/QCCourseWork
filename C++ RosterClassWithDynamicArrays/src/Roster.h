#ifndef ROSTER
#define ROSTER

#include "Student.h"
#include "date.h"
#define MAX_CAPACITY 10

#include <iostream>
#include <string>
using std::string;

class Roster{
	public:
		Roster();
		Roster(string name_, int code_, int credits_, string instructor_);
		//big three: destructor, copy constructor, and copy assignment constructor
		~Roster();
		Roster(const Roster& other);
		Roster& operator=(const Roster& other);

		string getName() const;
		int getCode() const;
		int getCredits() const;
		string getInstructor() const;
		Student& getStudent(int index_) const;
		int getIndex() const;

		void setName(string name_);
		void setCode(int code_);
		void setCredits(int credits_);
		void setInstructor(string name_);
		void setStudent(int index, Student st);

		void addStudent(Student st);
		void deleteStudent(int index_);

		int searchStudent(string last, string first);
		void output();

		friend std::ostream& operator<<(std::ostream& out, const Roster& r);
		friend std::istream& operator>>(std::istream& in, Roster& r);
		const Student& operator[](int index) const;

		void displayStu();
		void updateStudent(int index, const Student& updatedStudent);

	private:
		int index;
		string name;
		int code;
		int credits;
		string instructor;
		Student* students = new Student[MAX_CAPACITY]; //dynamic array
		void sort();
		void grow();


};

#endif
