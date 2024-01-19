#include "Roster.h"
#include "date.h"
#include "Student.h"
#include <iostream>
#include <fstream>
#include <string>


#include <iomanip>
#include <sstream>



using std::cout;
using std::endl;
using std::cin;
using std::string;

void writeStudent(std::fstream& myfile,Roster*& rosters, int index);
void writeRoster(std::fstream& myfile,Roster*& rosters, int index);


void save(std::fstream& myfile, Roster*& rosters, int& count);
void mainMenu(std::fstream& myfile, Roster*& list, int& count,
		char& mode);
void superMenu(std::fstream& myfile, Roster*& list, int& count, char& mode);
void userMenu(std::fstream& myfile, Roster*& list, int& count, char& mode);



void vadilityInt(string input);
void deliCheck(std::fstream& myfile, char d = '|');

Date newDate(std::fstream& myfile, char d = '/');
Roster newRoster(std::fstream& myfile,char d = '|');
Student newStudent(std::fstream& myfile, string fword, char d = '|');
void grow(Roster*& list, int &oriSize);
void expandRosters(std::fstream& myfile, Roster*& list, int &oriSize);

bool authenticate(std::fstream& myfile);

int main(){
	char mode;
	Roster * rosters = NULL;
	int count = 0; //number of rosters in the pointer array

	// cout and cin of Date class
	std::fstream myfile;
	myfile.open("/Users/fangfang/eclipse-workspace/try/src/rosters.txt", std::ifstream::in);
	//declare variables now for the Roster object


	if(myfile.fail()){
		cout << "Error: opening file" << endl;
		exit(1);

	}else if(myfile.is_open()){
		//this is the course info input
		string fword;
		while(!myfile.eof()){
			expandRosters(myfile, rosters, count);
			while(myfile >> fword && fword != "end_roster|") {
				rosters[count - 1].addStudent(newStudent(myfile,fword));
			}
		}
	}else {
        cout << "\nFile not open!" << endl;
    }

	myfile.close();

	mainMenu(myfile, rosters, count, mode);
	save(myfile, rosters, count);
	//cout << writeRoster(rosters, count);



}


void save(std::fstream& myfile, Roster*& rosters, int& count){
	myfile.open("/Users/fangfang/eclipse-workspace/try/src/rosters.txt", std::ofstream::out);
	writeRoster(myfile, rosters, count);
	//cout << rosters[0];
	myfile.close();

}
void writeStudent(std::fstream& myfile,Roster*& rosters, int index){
	//First1 | Last1|2000000|Freshmen|25|4.0|01/01/2001|09/01/2020

	double gpa;
	//cout << rosters[0];
	Roster* temp = &(rosters[index]);
	Student* st;
	string msg= "";
	for(int i = 0; i< temp->getIndex(); i++){
		std::stringstream stream;
		st = &(temp->getStudent(i+1)); //index in Roster refers to the index of element start from 1
		gpa = st->getGPA();

		stream << std::fixed << std::setprecision(2) << gpa;
		std::string s_gpa = stream.str();

		msg += st->getFirstName() + " | " + st->getLastName() +"|";
		msg += std::to_string(st->getID()) + "|" + st->getStanding() + "|" + std::to_string(st->getCredits())
				+ "|" + s_gpa
				+ "|" + st->getDOB() + "|" + st->getM_date() + "\n";
		myfile << msg;
		msg = "";
	}

}
void writeRoster(std::fstream& myfile,Roster*& rosters, int count){
	//class1 | 1 | 3 | TBA

	string msg = "";
	Roster* temp;
	//cout << rosters[0];
	for(int i=0; i< count-1; i++){
		temp = &(rosters[i]);
		msg += rosters[i].getName() + " | " + std::to_string(temp->getCode()) + " | "
				+ std::to_string(temp->getCredits()) + " | " + temp->getInstructor() + "\n";
		writeStudent(myfile, rosters, i);
		msg += "end_roster|";
		msg += "\n";
		myfile << msg;
		msg = "";
	}
	//to avoid a new line at the end
	temp = &(rosters[count-1]);
	msg += temp->getName() + " | " + std::to_string(temp->getCode()) + " | "
			+ std::to_string(temp->getCredits()) + " | " + temp->getInstructor() + "\n";
	writeStudent(myfile, rosters, count-1);
	msg += "end_roster|";

	myfile <<msg;

}

void mainMenu(std::fstream& myfile, Roster*& list, int& count, char& mode){
	do{
		cout << "\tA) Supervisor Mode " << endl
				<<"\tB) User Mode" << endl
				<< "\tC) Exit" << endl;
		cin >> mode;
	}while(!std::isalpha(mode));

	mode = std::toupper(mode); //to upper so only consider 3 cases.
	if(mode == 'A'){
		myfile.open("/Users/fangfang/eclipse-workspace/try/src/database.txt", std::ifstream::in);
		if(authenticate(myfile)){
			myfile.close();
			superMenu(myfile, list,count, mode);

		}else{
			myfile.close();
			//verification fail, then go back to the main menu
			mainMenu(myfile, list, count, mode);
		}
	}else if(mode == 'B'){
		userMenu(myfile, list, count, mode);
	}else if(mode == 'C'){
		//exit(1);
		cout << "Program ended" <<endl;
	}else{
		mainMenu(myfile, list, count, mode);
	}
}
int searchfor(Roster*& list, int& count, const int& code){
	int index = -1;

	for(int i = 0; i< count; i++){
		if(code == list[i].getCode()){
			index = i;
			break;
		}
	}
	return index;
}
void deleteRoster(Roster*& list, int& count, const int& code){
	int index = searchfor(list, count, code);

	if(index != -1){
		count--;
		for(int i = index; i< count; i++){
			list[i] = list[i+1]; //skip the deleted object
		}

	}else{
		cout << "No such Roster with code " << code << " exist. ";
	}

	//implement deleting code

}

void displayRoster(Roster*& list, int& count, const int& code){
	int index = searchfor(list, count, code);

	if(index != -1){
		cout << list[index];
	}else{
		cout << "There is no Roster with code " << code << "." << endl;
	}

}
void superMenu(std::fstream& myfile, Roster*& list, int& count, char& mode){
	int code_ ;
	int rloc = -1;
	int sloc = -1;
	string first, last;
	Student st;

	do{
		cout << "\t1) Create a new Roster (that will be stored in a growable array of Rosters in your main program)" << endl
		 << "\t2) Drop a Roster (selected by course number)" << endl
		 << "\t3) Display Roster information (selected by course number)" << endl
		 << "\t4) Display all Rosters (in your system)" << endl
		 << "\t5) Select a Roster to perform following operations: (ENTER 5)" << endl
		 << "\t\ta) Insert new Student to a Roster" << endl
		 << "\t\tb) Remove a Student from a Roster" << endl
		 << "\t\tc) Update a Student in a Roster" << endl
		 << "\t\td) List all Students in one Roster in sorted order" << endl
		 << "\t 6) Back to the MAIN MENU." << endl;
		cin >> mode;
	}while(!std::isdigit(mode));


	switch(mode) {
	  case '1':
		grow(list, count);
		cin >> list[count-1];
		//
		//cout << list[count-1];

	    // code block
	    break;
	  case '2':
		cout << "Enter the course code to drop the Roster: " << endl;
		cin >> code_;
		deleteRoster(list,count,code_);
		// code block
	    break;
	  case '3':
		cout << "Enter the course code to display the Roster: " << endl;
		cin >> code_;
		displayRoster(list,count,code_);
		break;
	  case '4':
		for(int i = 0; i< count; i++){
			cout << list[i];
		}
		break;
	  case '5':
		do{
			cout << "a|b|c|d" << endl;
			cin >> mode;
		}while(!std::isalpha(mode));
		mode = tolower(mode);

		switch(mode){
			case 'a':
				cout << "Enter the course code for the Roster: " << endl;
				cin >> code_;
				rloc = searchfor(list,count,code_);
				cout << "Add student into the Roster " << code_ <<": " << endl;
				cin >> st;
				list[rloc].addStudent(st);

				break;
			case 'b':
				cout << "Enter the course code for the Roster: " << endl;
				cin >> code_;
				rloc = searchfor(list,count,code_);
				cout <<"Delete student from the Roster " << code_ << ": " << endl;
				cout << "Enter the last and first name of the student: \n FirstName LastName \n";
				cin >> first >> last;
				sloc = list[rloc].searchStudent(last, first) -1 ;
				if(sloc != -1){
					list[rloc].deleteStudent(sloc);
				}
				else{
					cout << "This student doesn't exist in your Roster.";
				}
				break;

			case 'c':

				cout << "Enter the course code for the Roster: " << endl;
				cin >> code_;
				rloc = searchfor(list,count,code_);
				cout <<"Update student from the Roster " << code_ << ": " << endl;
				cout << "Enter the last name of the student: \n";
				cin >> last;
				cout << "Enter the first name: " << endl;
				cin >> first;

				sloc = list[rloc].searchStudent(last, first)-1;

				if(sloc != -1){
					cout << list[rloc][sloc];
					cout << "Enter new info for this student: " << endl;
					cin >> st;
					list[rloc].updateStudent(sloc,st);
				}
				else{
					cout << "This student doesn't exist in your Roster.";
				}
				break;

			case 'd':
				cout << "Enter the course code for the Roster: " << endl;
				cin >> code_;
				rloc = searchfor(list,count,code_);
				cout <<"Display all students from the Roster " << code_ << ": " << endl;
				list[rloc].displayStu();
				break;

			default:
				superMenu(myfile,list,count,mode);
		}

		break;
	  case '6':
		  mainMenu(myfile,list,count,mode);
		  break;
	  default:
		superMenu(myfile, list, count, mode);
	    // code block
	}

	char stay;
	do{
		cout << "Continue in Supervisor Mode ? Y/N" << endl;
		cin >> stay;
	}while(!std::isalpha(stay));

	if(toupper(stay) == 'Y'){
		superMenu(myfile, list, count, mode);
	}else{
		mainMenu(myfile, list, count, mode);
	}

}

void userMenu(std::fstream& myfile, Roster*& list, int& count, char& mode){
	myfile.close();
	int code_ ;
	int rloc = -1;
	int sloc = -1;
	string first, last;
	Student st;

	do{
		cout << "\tSelect a Roster to perform following operations:" << endl
			 << "\t\ta) Insert new Student to a Roster" << endl
			 << "\t\tb) Remove a Student from a Roster" << endl
			 << "\t\tc) Update a Student in a Roster" << endl;
		cin >> mode;
	}while(!std::isalpha(mode));

	mode = tolower(mode);

	switch(mode){
		case 'a':
			cout << "Enter the course code for the Roster: " << endl;
			cin >> code_;
			rloc = searchfor(list,count,code_);
			cout << "Add student into the Roster " << code_ <<": " << endl;
			cin >> st;
			list[rloc].addStudent(st);

			break;
		case 'b':
			cout << "Enter the course code for the Roster: " << endl;
			cin >> code_;
			rloc = searchfor(list,count,code_);
			cout <<"Delete student from the Roster " << code_ << ": " << endl;
			cout << "Enter the last and first name of the student: \n FirstName LastName \n";
			cin >> first >> last;
			sloc = list[rloc].searchStudent(last, first) -1 ;
			if(sloc != -1){
				list[rloc].deleteStudent(sloc);
			}
			else{
				cout << "This student doesn't exist in your Roster.";
			}
			break;

		case 'c':

			cout << "Enter the course code for the Roster: " << endl;
			cin >> code_;
			rloc = searchfor(list,count,code_);
			cout <<"Update student from the Roster " << code_ << ": " << endl;
			cout << "Enter the last name of the student: \n";
			cin >> last;
			cout << "Enter the first name: " << endl;
			cin >> first;

			sloc = list[rloc].searchStudent(last, first)-1;

			if(sloc != -1){
				cout << list[rloc][sloc];
				cout << "Enter new info for this student: " << endl;
				cin >> st;
				list[rloc].updateStudent(sloc,st);
			}
			else{
				cout << "This student doesn't exist in your Roster.";
			}
			break;
		default:
			userMenu(myfile, list, count, mode);
	}

	char stay;
	do{
		cout << "Continue in User Mode ? Y/N" << endl;
		cin >> stay;
	}while(!std::isalpha(stay));

	if(toupper(stay) == 'Y'){
		userMenu(myfile, list, count, mode);
	}else{
		mainMenu(myfile, list, count, mode);
	}
}


void vadilityInt(string input){
	bool errorMsg = false;
	for(int i = 0; i < input.length(); i++) {
		if( !isdigit( input[i] )) {
			errorMsg = true;
			break;
		}
	}
	if(!errorMsg){
		cout << "ERROR: One of the input is not valid as an integer.";
		exit(1);
	}
}

void deliCheck(std::fstream& myfile, char d){
	char deli;
	myfile >> deli;
	if(deli != d){
		string errorL;
		cout << "Error: the file is not in the right format. deli(" << deli << ")and not(" << d << ")" << endl;
		getline(myfile, errorL);
		cout << errorL;
		exit(1);
	}
}
Roster newRoster(std::fstream& myfile, char d){

	string name, instructor, codeTest, creditTest;
	int code, credits;
	//read them from the file
	myfile >> name;
	deliCheck(myfile);

	myfile >> code;
	deliCheck(myfile);

	myfile >> credits;
	deliCheck(myfile);

	myfile >> instructor;

	return Roster(name, code, credits, instructor);

}
void grow(Roster*& list, int& oriSize){
	Roster* temp = new Roster[oriSize + 1]; // Create a new array with expanded size

	for(int i = 0; i < oriSize; i++){
		temp[i] = list[i];
	}
	delete[] list;

	list = temp;
	oriSize++;
	//cout << list[0] << list[1];
}
void expandRosters(std::fstream& myfile, Roster*& list, int &oriSize){
	grow(list, oriSize);

	list[oriSize-1] = newRoster(myfile);
	//cout << list[0];

	//expand the size by one for later Roster
}


Student newStudent(std::fstream& myfile, string fword, char d){
	//student1 first name | student1 last name|sid|standing|credits|gpa|mm/dd/yyyy|mm/dd/yyyy
	int IDnum;
	string temp;

	string lastName;
	string firstName = fword;
	string standing;
	int credits;
	double GPA;
	Date DOB;
	Date mDate;

	//first word is read when we check if there are more students
	//myfile >> firstName;
	deliCheck(myfile, d);


	std::getline(myfile >> std::ws, lastName, d);
	myfile >> IDnum;
	deliCheck(myfile);

	std::getline(myfile, standing,d);

	myfile >> credits;
	deliCheck(myfile);

	myfile >> GPA;
	deliCheck(myfile);

	DOB = newDate(myfile);
	deliCheck(myfile);

	mDate = newDate(myfile);

	return Student(IDnum, lastName, firstName, credits, GPA, DOB, mDate, standing);
}

Date newDate(std::fstream& myfile, char d){
	int month, day, year;
	string temp;

	myfile >> month;
	deliCheck(myfile, d);

	myfile >> day;
	deliCheck(myfile, d);

	myfile >>year;

	return Date(month, day, year);
}

bool authenticate(std::fstream& myfile){
	string username, password;
	cout << "Enter your username and password: (with a space in between)" << endl;
	cout << "EX: User 123" << endl;
	cin >> username;
	cin >> password;

	string supername, superpass;
	while(!myfile.eof()){
		myfile >> supername;
		myfile >> superpass;
		if(supername == username && superpass == password){
			return true;
		}
	}
	return false;
}

