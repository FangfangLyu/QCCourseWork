#include "Student.h"
#include "date.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::to_string;


Student::Student()
	:IDnum(0),lastName("Joe"), firstName("Doe"), standing("Lower Freshman"),
	 credits(0),GPA(0.0),DOB(Date()),matriculation_date(Date())
{
	//default constructor
}
void Student::output() const{
	cout<< "ID: " << IDnum << endl << firstName << " " << lastName << "'s info: " << endl << "DOB: " << DOB << endl;
	cout << "Matriculation date: " << matriculation_date << endl << "Current class standing: " << standing << endl << "Earned: " << credits << " credits with GPA: " << GPA << endl<<endl;

}
//friend

//friend
std::ostream& operator<<(std::ostream& out, const Student& stu){
	out << "ID: " << stu.IDnum << endl << stu.firstName << " " << stu.lastName << "'s info: " << endl << "DOB: " << stu.DOB << endl
			<< "Matriculation date: " << stu.matriculation_date << endl
			<< "Current class standing: " << stu.standing << endl
			<< "Earned: " << stu.credits << " credits with GPA: " << stu.GPA << endl;
	return out;

}

Student::Student(int newID, string newLname, string newFname, int newCredit, double newGPA, Date& DOB, Date& matri)
	:IDnum(newID), lastName(newLname),firstName(newFname),
	 credits(newCredit),GPA(newGPA),DOB(DOB),matriculation_date(matri)
{
	//date object is contained in student,I only did shallow copy
	setStanding();
}
Student::Student(int newID, string newLname, string newFname, int newCredit, double newGPA, Date& DOB, Date& matri, string standing)
	:IDnum(newID), lastName(newLname),firstName(newFname),
	 credits(newCredit),GPA(newGPA),DOB(DOB),matriculation_date(matri), standing(standing)
{
	//date object is contained in student,I only did shallow copy
}
int Student::getID() const{
	return IDnum;
}

string Student::getLastName() const{
	return lastName;
}
void Student::setLastName(string newLname){
	lastName = newLname;
}
string Student::getFirstName() const{
	return firstName;
}
void Student::setFirstName(string newFname){
	firstName = newFname;
}
int Student::getCredits() const{
	return credits;
}
void Student::setCredits(int newCredit){
	credits = newCredit;
	setStanding();

}
double Student::getGPA() const{
	return GPA;
}
void Student::setGPA(double newGPA){
	GPA = newGPA;
}
Date& Student::getDOB(){
	return DOB;
}
void Student::setDOB(Date& newDOB){
	DOB = newDOB;
}
Date& Student::getM_date(){
	return matriculation_date;
}
void Student::setM_date(Date& newDate){
	matriculation_date = newDate;
}
string Student::getStanding() const{
	return standing;
}
void Student::setStanding(){
	int index = 1;
		//if the credit is greater than the score for the first rank, go up the rank index by 1
		//the rank index has a maximum of 8 ranks, stop when it is going to exceed.
	while(credits>=index*15 && index<=7){
		index++;
	}
	standing = rank[index-1];

}
//input and output functions
void Student::input(){
	cout << "Enter the student's last name:" << endl;
	cin >> lastName;
	cout << "Enter the student's first name: \n";
	cin >> firstName;
	cout << "Enter the student's total number of credits earned: \n";
	cin >> credits;
	cout << "Enter the student's GPA: \n";
	cin >> GPA;
	cout << "Enter the student's DOB: \n";
	cin >> DOB;
	cout << "Enter the student's date of matriculation \n";
	cin >> matriculation_date;
	setStanding();
}
bool Student::operator==(const Student &other) const{
	if(this == &other){
		//if the same memory address
		return true;
	}else{
		//if not, compare last name, then first name, then idNum
		if(other.getLastName() == lastName && other.getFirstName() == firstName && other.getID() == IDnum){
			return true;
		}
	}
	return false;
}

bool Student::operator!=(const Student &other) const{
	if(this == &other){
		return false;
	}else{
		if(other.lastName != lastName || other.firstName != firstName || other.IDnum != IDnum){
			return true;
		}
	}
	return false;
}
bool Student::operator<(const Student &other) const
{
	if(this == &other){
		return false;
	}else if(other.getLastName() == lastName && other.getFirstName() == firstName && other.getID() == IDnum)
	{
		return false;
	}else{
		//if they are not equal, then compare
		for(int i = 0; i < lastName.length(); i++){
			if(lastName[i]<other.getLastName()[i]){
				return true; //if the corresponding letter is smaller, then true
			}if(lastName[i]>other.getLastName()[i]){
				return false;
			}
		}
		for(int i = 0; i < firstName.length(); i++){
			if(firstName[i] < other.getLastName()[i]){
				return true;
			}if(lastName[i]>other.getLastName()[i]){
				return false;
			}
		}
		if(IDnum <other.getID()){
			return true;
		}
	}
	return false;
}
bool Student::operator>(const Student &other) const{
	if(this == &other) {
		return false;
	}else if(lastName == other.getLastName() && firstName == other.getFirstName() && IDnum == other.getID()){

		return false;
	}else{//if they are not equal, then compare
                for(int i = 0; i < lastName.length(); i++){
                        if(lastName[i]>other.getLastName()[i]){
                                return true; //if the corresponding letter is smaller, then true
                        }if(lastName[i]<other.getLastName()[i]){
                                return false;
                        }
                }
                for(int i = 0; i < firstName.length(); i++){
                        if(firstName[i] > other.getLastName()[i]){
                                return true;
                        }if(lastName[i]<other.getLastName()[i]){
                                return false;
                        }
                }
		if(IDnum > other.getID()){
			return true;
		}
	}
	return false;

}

bool Student::operator<=(const Student &other) const{
	if(*this==other || *this < other){
		return true;
	}
	return false;
}

bool Student::operator>=(const Student &other) const{
	if(*this == other || *this >other){
		return true;
	}
	return false;
}


//friend
std::istream& operator>>(std::istream& in, Student& stu){
	cout << "Please enter the ID num of the student: " << endl;
	in >> stu.IDnum;

	cout << "Please enter the first name of the student: " << endl;
	in >> stu.firstName;

	cout << "Please enter the last name of the student: " << endl;
	in >> stu.lastName;

	cout << "Please enter the credits of the student: " << endl;
	in >> stu.credits;

	cout << "Please enter the GPA: " <<endl;
	in >> stu.GPA;

	cout << "Please enter the birth date of the student: " << endl;
	in >> stu.DOB;

	cout << "Please enter the matriculation date of the student: " << endl;
	in >> stu.matriculation_date;



/*
	stu.setID(ID);
	stu.setLast(last);
	stu.firstName = first;
        stu.credits = credits;
	stu.GPA = GPA;
	stu.DOB = DOB;
	stu.matriculation_date = matriculation_date;
*/
	return in;
}

