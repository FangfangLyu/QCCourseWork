#include "Roster.h"
#include "Student.h"
#include "date.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::to_string;

Roster::Roster()
	:name("ClassTemplate"), code(-1), credits(0),index(0), instructor("Nobody")
{
	//empty
	// this index counts the number of students in the list
}

Roster::Roster(string name_, int code_, int credits_, string instructor_)
	:name(name_), code(code_), credits(credits_), index(0), instructor(instructor_)
{
	//empty
}

Roster::~Roster(){
	if(index != 0){
		delete[] students;
	}
}
Roster::Roster(const Roster& other): name(other.getName()), code(other.getCode()), credits(other.getCredits()), index(other.getIndex()), instructor(other.getInstructor()){
	index = other.index;
	//Note: I don't actually have to do getName, getCode ... etc (becasue the member function have access to the privates fields of the same class object.
	if(index != 0){
		students = new Student[index];
		for (int i = 0; i < index; ++i) {
			students[i] = other[i];
		}
	}else{
		students = NULL;
	}
}
Roster& Roster::operator=(const Roster& other) {
		if (this != &other) { // Check for self-assignment
			if(students!= NULL){
				delete[] students;
			}
			index = other.index;
			if(index == 0){
				students = NULL;
			}else{
				students = new Student[index];
				for (int i = 0; i < index; ++i) {
					students[i] = other.students[i];
				}
			}
		}
		name = other.name;
		code = other.code;
		credits = other.credits;
		instructor = other.instructor;
        return *this;
}

string Roster::getName() const{
	return name;
}
int Roster::getCode() const{
	return code;
}
int Roster::getCredits() const{
	return credits;
}
string Roster::getInstructor() const{
	return instructor;
}
Student& Roster::getStudent(int index_) const{
	if(index_>=1 && index_<= index){
		return students[index_-1];
	}else{
		throw std::out_of_range("No such student " + std::to_string(index_) + " exists");
	}
}

int Roster::getIndex() const{
	return index;
}


void Roster::setName(string name_)
{
	name = name_;
}

void Roster::setCode(int code_){
	code = code_;
}
void Roster::setCredits(int credits_){
	if(credits_>=0 && credits_<=4){
		credits = credits_;
	}
}
void Roster::setInstructor(string name_){
	instructor = name_;
}
void Roster::setStudent(int index, Student st){
	students[index-1] = st;

}
void Roster::grow(){
	Student* temp = new Student[index + 1]; //index is the size of the array
	//make the array one larger than its current size
	for(int i = 0; i < index; i++){
		//copy all current object in student into the new array temp.
		temp[i] = students[i];
	}
	delete[] students;
	students = temp;

}

void Roster::addStudent(Student st){
	if(index >=10){
		//cout <<"You reached the capacity of the list, the array size now get grow by 1." << endl;
		grow();
	}
	if (students == NULL) {
	        students = new Student[MAX_CAPACITY]; // Allocate memory for students if it's null
	}
	//cout << index;
	students[index++] = st;
	sort();


}
void Roster::deleteStudent(int index_){
	if(index>0 & index <= 10){
		for(int i = index_-1; i<index-1; i++){
			students[i] = students[i+1];
		}

		index--;

	}else if(index>10){

		Student* temp = new Student[index-1];
		for(int i = 0; i<index_; i++){
			temp[i] = students[i];
		}
		for(int i = index_-1; i<index-1; i++){
			temp[i] = students[i+1];
		}
		delete[] students;
		students = temp;
		index--;
	}

}

int Roster::searchStudent(string last, string first){

	for(int i = 0; i<index; i++){
		if(students[i].getLastName() == last){
			if(students[i].getFirstName() == first){
				cout << "We find the student "<<  first << " " << last << " as student " << (i+1) << endl;
				return i+1;
			}
		}
	}
	cout << "We don't have the student " <<  first << " " << last << " in the roster." << endl;

	return 0;
}

void Roster::output(){

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl
		 << "Class			: " << name << endl
		 << "Instructor		: " << instructor << endl
		 << "Class Code		: " << code << endl
		 << "Class Credit		: " << credits << endl
		 <<  "Class roster		: " << "( " << index << ")" << endl;

	for(int i = 0; i<index;i++){
		cout << "---------------------------" << endl
			 << "Student " << (i+1) << "'s info: " <<endl;
		students[i].output();
	}


	if(index == 0){
		cout <<"	***Nobody has enrolled in this course.***" <<endl;
	}
	cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl <<endl << endl;


}
//friend function
std::ostream& operator<<(std::ostream& out, const Roster& r){
	out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl
		 << "Class			: " << r.name << endl
		 << "Instructor		: " << r.instructor << endl
		 << "Class Code		: " << r.code << endl
		 << "Class Credit		: " << r.credits << endl
		 <<  "Class roster		: " << "( " << r.index << ")" << endl;

	for(int i = 0; i<r.index;i++){
		out << "---------------------------" << endl
			 << "Student " << (i+1) << "'s info: " <<endl;
		out << r.students[i];
	}

	if(r.index == 0){
		out <<"	***Nobody has enrolled in this course. ***" <<endl;
	}
	out <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl <<endl << endl;
	return out;
}
std::istream& operator>>(std::istream& in, Roster& r){
	cout << "We will  create a student rooster for your class: (Please follow instruction" << endl;
	cout << "Enter the course name: " ;
	in >> r.name;
	cout << "Enter the course code: ";
	in >> r.code;
	cout << "Enter the credits: ";
	in >> r.credits;
	cout << "Enter the instructor Name: ";
	in >> r.instructor;
	cout << "Enter the number of students in your class: " ;
	int size;
	in >> size;

	Student temp;
	/*
	if(size>10){
		cout << "ERROR: The max size is 10 for each roster. ";
		exit(1);
	}*/

	for (int i = 0; i < size; i++){
		cout << "Enter the information for student " << (i+1) << ":" << endl;
		in >> temp;
		r.addStudent(temp);
	}
	r.sort();
	return in;
}
void Roster::displayStu(){
	sort();
	for(int i = 0; i < index; i++){
		cout << students[i];
	}
}
void Roster::sort(){
	//bubble sort
	for(int j=index; j>1; j--){
		for(int i=0; i<(j-1); i++){
			if(students[i] > students[i+1]){
				Student temp = students[i+1];
				students[i+1] = students[i];
				students[i] = temp;
			}
		}
	}
}
const Student& Roster::operator[](int index_i) const{
	if(index_i < index) {
		return students[index_i];
	}else{
		cout << "Error: [] operator is not applicable for index index_i";
		exit(1);
	}
}

void Roster::updateStudent(int index_, const Student& updatedStudent) {
    if (index_ >= 0 && index_ < index) {
        students[index_] = updatedStudent;
    } else {
        // Handle invalid index
        cout << "Invalid for student update." << endl;
    }
}


