#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

class NodeVaccine {
	public:
		string number;
		string vaccineName;
		string amount;
		string maxDose;
		string remain;
		NodeVaccine *link;
		NodeVaccine(string number, string vaccineName, string amount, string maxDose, string remain) {
			this->number = number;
			this->vaccineName = vaccineName;
			this->amount = amount;
			this->maxDose = maxDose;
			this->remain = remain;
		}
};

class Vaccine {
	private:
		NodeVaccine *head;
		NodeVaccine *tail;
		int count;
	public:
		Vaccine() {
			this->head = NULL;
			this->tail = NULL;
			count = 0;
		}
		
		void add(string number, string vaccineName, string amount, string maxDose, string remain) {
			NodeVaccine *temp = new NodeVaccine(number, vaccineName, amount, maxDose, remain);
			temp->link = NULL;
			if(head == NULL) {
				head = temp;
				tail = temp;
			} else {
				tail->link = temp;
				tail = temp;
			}
			count++;
		}
		
		
		void addRead() {
			fstream readFile;
			readFile.open("vaccine.txt", ios::in);
			string line;
			string readNumber, readVaccineName, readAmount, readMaxDose, readRemain;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readNumber = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readVaccineName = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readMaxDose = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readAmount = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readRemain = line;
					
					Vaccine::add(readNumber, readVaccineName, readAmount, readMaxDose, readRemain);
				}
			}
	
			readFile.close();
		}
		
		string getVaccineName(string vaccineType) {
			NodeVaccine *temp = head;
			for(int i=1; i<=count; i++) {
				if(temp->number == vaccineType) 
					return temp->vaccineName;
				temp = temp->link;
			}
			return "Not Vaccinated";
		}
		
		string getMaxDose(string vaccineType) {
			NodeVaccine *temp = head;
			for(int i=1; i<=count; i++) {
				if(temp->number == vaccineType) 
					return temp->maxDose;
				temp = temp->link;
			}
		}
					
		void show() {
			if(head == NULL) {
				cout << "No data" << endl;
				return;
			}
			NodeVaccine *temp = head;
			int total = 0, totalAmount = 0, totalRemain = 0;
			int numAmount, numRemain;
			cout << "===========================================================" << endl;
			cout << setw(8) << left << "   No." 
				<< setw(25) << left << "Vaccine" 
				<< setw(15) << left << "Amount" 
				<< "Remain" << endl;
			cout << "===========================================================" << endl;
			for(int i=0; i<count; i++) {
				cout << setw(8) << left << "   " + temp->number + "."
					<< setw(25) << left << temp->vaccineName
					<< setw(5) << left << temp->amount << setw(10) << left << "Dose" 
					<< setw(5) << left << temp->remain << "Dose" << endl;
					
				stringstream streamAmount(temp->amount);
				streamAmount >> numAmount;
				stringstream streamRemain(temp->remain);
				streamRemain >> numRemain;
				totalAmount += numAmount;
				totalRemain += numRemain;
				temp = temp->link;
			}
			cout << "===========================================================" << endl;
			ostringstream ssTotalAmount;
     		ssTotalAmount << totalAmount;
     		string strTotalAmount = ssTotalAmount.str();
			cout << setw(33) << left << "   Total" 
			<< setw(5) << left << strTotalAmount << setw(10) << left << "Dose" 
			<< setw(5) << left << totalRemain << "Dose" << endl;
			cout << "===========================================================" << endl;
		}
		
		~Vaccine() {
			for(int i=0; i<count; i++){
				NodeVaccine *temp = head;
				head = head->link;
				delete temp;
				temp = NULL;
			}
			head = NULL;
			tail = NULL;
		}
		
};

class NodeHospital {
	public:
		string hospitalId;
		string hospitalName;
		NodeHospital *link;
		NodeHospital(string hospitalId, string hospitalName) {
			this->hospitalId = hospitalId;
			this->hospitalName = hospitalName;
		}
};

class Hospital {
	private:
		NodeHospital *head;
		NodeHospital *tail;
		int count;
	public:
		Hospital() {
			this->head = NULL;
			this->tail = NULL;
			count = 0;
		}
		
		void add(string hospitalId, string hospitalName) {
			NodeHospital *temp = new NodeHospital(hospitalId, hospitalName);
			temp->link = NULL;
			if(head == NULL) {
				head = temp;
				tail = temp;
			} else {
				tail->link = temp;
				tail = temp;
			}
			count++;
		}
		
		
		void addRead() {
			fstream readFile;
			readFile.open("hospital.txt", ios::in);
			string line;
			string readHospitalId, readHospitalName;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readHospitalId = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readHospitalName = line;
									
					Hospital::add(readHospitalId, readHospitalName);
				}
			}
	
			readFile.close();
		}
		
		string getHospitalName(string id) {
			if(id == "0")
				return "-";
			NodeHospital *temp = head;
			for(int i=1; i<=count; i++) {
				if(id == temp->hospitalId) 
					return temp->hospitalName;
				temp = temp->link;
			}
			return "-";
		}
			
};

class NodePeople {
	public:
		string id;
		string password;
		string name;
		string vaccineType;
		string acceptDose;
		string date1;
		string date2;
		string location;
		NodePeople *link;
		NodePeople(string id, string password, string name, string vaccineType, string acceptDose, string date1, string date2, string location) {
			this->id = id;
			this->password = password;
			this->name = name;
			this->vaccineType = vaccineType;
			this->acceptDose = acceptDose;
			this->date1 = date1;
			this->date2 = date2;
			this->location = location;
		}
};

class People {
	private:
		Vaccine vaccine;
		Hospital hospital;
		NodePeople *head;
		NodePeople *tail;
		int count;
	public:
		People() {
			this->head = NULL;
			this->tail = NULL;
			count = 0;
		}
		
		void add(string id, string password, string name, string vaccineType, string acceptDose, string date1, string date2, string location) {
			NodePeople *temp = new NodePeople(id, password, name, vaccineType, acceptDose, date1, date2, location);
			temp->link = NULL;
			if(head == NULL) {
				head = temp;
				tail = temp;
			} else {
				tail->link = temp;
				tail = temp;
			}
			count++;
		}
		
		void addRead() {
			vaccine.addRead();
			hospital.addRead();
			fstream readFile;
			readFile.open("people.txt", ios::in);
			string line;
			string readId, readPassword, readName, readVaccineType, readAcceptDose, readDate1, readDate2, readLocation;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readId = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readPassword = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readName = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readVaccineType = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readAcceptDose = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readDate1 = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readDate2 = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readLocation = line;
					
					People::add(readId, readPassword, readName, readVaccineType, readAcceptDose, readDate1, readDate2, readLocation);
				}
			}
	
			readFile.close();
		}
					
		void show() {
			if(head == NULL) {
				cout << "No data" << endl;
				return;
			}
			NodePeople *temp = head;
			cout << "========================================================================================================================================" << endl;
			cout << setw(8) << left << "   NO." 
				<< setw(15) << left << "Student ID" 
				<< setw(20) << left << "Name" 
				<< setw(20) << left << "Vaccinated" 
				<< setw(10) << left << "Status" 
				<< setw(15) << left << "Date#1" 
				<< setw(15) << left << "Date#2" 
				<< "Location" << endl;
			cout << "========================================================================================================================================" << endl;
			int j = 1;
			for(int i=1; i<=count; i++) {
				if(temp->id.length() == 8) {
					ostringstream ss;
     				ss << j;
     				string strNo = ss.str();
					cout << setw(8) << left << "   " + strNo + "."
						<< setw(15) << left << temp->id
						<< setw(20) << left << People::covertName(temp->id)
						<< setw(20) << left << vaccine.getVaccineName(temp->vaccineType) 
						<< setw(10) << left << People::getStatus(temp->id).substr(0, People::getStatus(temp->id).find(" ")); 
					if(temp->date1 != "-") {
						string date1 = People::getDate1(temp->id);
						cout << setw(15) << left << date1.substr(0, date1.length()-4) + date1.substr(date1.length()-2, 2);
					} else {
						cout << setw(15) << left << People::getDate1(temp->id);						
					}
					if(temp->date2 != "-") {
						string date2 = People::getDate2(temp->id);
						cout << setw(15) << left << date2.substr(0, date2.length()-4) + date2.substr(date2.length()-2, 2);
					} else {
						cout << setw(15) << left << People::getDate2(temp->id);	
					}
					cout << hospital.getHospitalName(temp->location) << endl;

					temp = temp->link;
				}
				j++;
			}
			cout << "========================================================================================================================================" << endl;
		}
		
		int checkLogin(string username, string password) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) {
					if(password == temp->password) {
						return 1; // success
					} else {
						return 2; // wrong password
					}
				} 
				temp = temp->link;
			}
			return 3; // not found username
		}
		
		string covertName(string id) {
			string fullName;
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(id == temp->id) {
					fullName = temp->name;
					break;
				}
				
				temp = temp->link;
			}
			int blank = 0, blankPositon;
			string name;
			for(int i=0; i<fullName.length(); i++) {
				if(fullName[i] == ' ') {
					blank++;
					blankPositon = i;
				}
			}
			
			if(blank == 2) {
				name = fullName.substr(0,fullName.find(" "));
				name += " " + fullName.substr(fullName.find(" ")+1, 1);
				name += ". " + fullName.substr(blankPositon+1, fullName.length()-blankPositon);
			} else {
				name = fullName.substr(0, 1)+ ". " + fullName.substr(fullName.find(" ")+1, fullName.length()-blankPositon);
			}
			return name;
		}
		
		string getVaccineName(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					return vaccine.getVaccineName(temp->vaccineType);
				
				temp = temp->link;
			}
			return "-";
		}
		
		string getStatus(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					break;
				
				temp = temp->link;
			}
			if(temp->vaccineType == "0") {
				return "-";
			} else {
				return temp->acceptDose + "/" + vaccine.getMaxDose(temp->vaccineType) + " Dose";
			}

		}
		
		string getDate1(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					break;
				
				temp = temp->link;
			}
			if(temp->date1 != "-") {
				string month = "";
				int year1;
				stringstream streamYear1(temp->date1.substr(6, 4));
				streamYear1 >> year1;
				ostringstream ssYear1;
				ssYear1 << year1 + 543;
				string strYear1 = ssYear1.str();
				if(temp->date1.substr(3, 2) == "01") {
					month = "Jan";
				} else if(temp->date1.substr(3, 2) == "02") {
					month = "Feb";
				} else if(temp->date1.substr(3, 2) == "03") {
					month = "Mar";
				} else if(temp->date1.substr(3, 2) == "04") {
					month = "Apr";
				} else if(temp->date1.substr(3, 2) == "05") {
					month = "May";
				} else if(temp->date1.substr(3, 2) == "06") {
					month = "Jun";
				} else if(temp->date1.substr(3, 2) == "07") {
					month = "Jul";
				} else if(temp->date1.substr(3, 2) == "08") {
					month = "Aug";
				} else if(temp->date1.substr(3, 2) == "09") {
					month = "Sep";
				} else if(temp->date1.substr(3, 2) == "10") {
					month = "Oct";
				} else if(temp->date1.substr(3, 2) == "11") {
					month = "Nov";
				} else if(temp->date2.substr(3, 2) == "12") {
					month = "Dec";
				}
				return temp->date1.substr(0, 2) + " " + month + " " + strYear1;
			} else {
				return temp->date1;
			} 
						
		}
		
		string getDate2(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					break;
				
				temp = temp->link;
			}
			if(temp->date2 != "-") {
				string month = "";
				int year2;
				stringstream streamYear2(temp->date2.substr(6, 4));
				streamYear2 >> year2;
				ostringstream ssYear2;
				ssYear2 << year2 + 543;
				string strYear2 = ssYear2.str();
				if(temp->date2.substr(3, 2) == "01") {
					month = "Jan";
				} else if(temp->date2.substr(3, 2) == "02") {
					month = "Feb";
				} else if(temp->date2.substr(3, 2) == "03") {
					month = "Mar";
				} else if(temp->date2.substr(3, 2) == "04") {
					month = "Apr";
				} else if(temp->date2.substr(3, 2) == "05") {
					month = "May";
				} else if(temp->date2.substr(3, 2) == "06") {
					month = "Jun";
				} else if(temp->date2.substr(3, 2) == "07") {
					month = "Jul";
				} else if(temp->date2.substr(3, 2) == "08") {
					month = "Aug";
				} else if(temp->date2.substr(3, 2) == "09") {
					month = "Sep";
				} else if(temp->date2.substr(3, 2) == "10") {
					month = "Oct";
				} else if(temp->date2.substr(3, 2) == "11") {
					month = "Nov";
				} else if(temp->date2.substr(3, 2) == "12") {
					month = "Dec";
				}
				return temp->date2.substr(0, 2) + " " + month + " " + strYear2;
			} else {
				return temp->date2;
			} 
						
		}
		
		string getLocation(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					return hospital.getHospitalName(temp->location);
				
				temp = temp->link;
			}
			return "-";
		}
		
		void showPersonalInfo(string searchName) {
			string choice;
			NodePeople *temp = head;
			int find = 0;
			for(int i=0; i<count ;i++) {
				if(searchName == temp->name) {
					find = 1;
					break;
				}
				temp = temp->link;
			}
			if(find == 1) {
				cout << "---------------------------------------------" << endl;
				cout << "ID: " << temp->id << endl;
				cout << "Name: " << People::covertName(temp->id) << endl;
				cout << "---------------------------------------------" << endl;
				cout << "Vaccinated : " << People::getVaccineName(temp->id) << endl;
				cout << "Status : " << People::getStatus(temp->id) << endl;
				cout << "Date#1 : " << People::getDate1(temp->id) << endl;
				cout << "Date#2 : " << People::getDate2(temp->id) << endl;
				cout << "Location : " << People::getLocation(temp->id) << endl;
			} else {
				cout << "\n\t!! Not Found !!\n" << endl;
			}

		}
		
		~People() {
			for(int i=0; i<count; i++){
				NodePeople *temp = head;
				head = head->link;
				delete temp;
				temp = NULL;
			}
			head = NULL;
			tail = NULL;
		}
		
};

int main() {
	People people;
	people.addRead();
	string menuStart; // before login
	string mainMenu; // after login
	string choice = "0";
	int loginCheck;
	string username, password;

	do {
		do {
			system("cls");
			cout << "============================" << endl;
			cout << "BUU PROMPT" << endl;
			cout << "============================" << endl;
			cout << "  1.Log in" << endl;
			cout << "  2.Exit" << endl; 
			cout << "============================" << endl;
			if(loginCheck == 2) {
				cout << "Wrong password" << endl;
			} else if(loginCheck == 3) {
				cout << "Not found this user" << endl;
			}
			cout << "  Enter menu: ";
			cin >> menuStart;
			if(menuStart == "1") {
				cout << "============================" << endl;
				cout << "BUU PROMPT" << endl;
				cout << "LOGIN" << endl;
				cout << "============================" << endl;
				cout << "ID : ";
				cin >> username;
				cout << "Password : ";
				cin >> password;
				loginCheck = people.checkLogin(username, password);
			
			} else {
				return 0; // exit program
			}			
		} while(loginCheck != 1);
		
		do {
			system("cls");
			cout << "=============================================" << endl;
			if(username.length() == 8) {
				cout << setw(25) << left << "BUU PROMPT"  << setw(20) << right << "For Student" << endl;
			} else {
				cout << setw(25) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;
			}
			cout << "\nID: " << username << endl;
			cout << "Name: " << people.covertName(username) << endl;
		
			cout << "=============================================" << endl;
			if(username.length() == 10) {
				cout << "1. See booking list" << endl;
				cout << "2. Search Name" << endl;
			} else {
				cout << "1. See booking history" << endl;
			}
		
			cout << "3. Go back" << endl;
			cout << "4. Exit" << endl; 
			cout << "=============================================" << endl;
			cout << "Enter menu: ";
			cin >> mainMenu;
		
			if(mainMenu == "1") {
				if(username.length() == 10) {
					people.show();
					cout << "1. Go back" << endl;
					cout << "2. Exit" << endl; 
					do {
						cout << "Enter menu: ";
						cin >> choice;
					} while(choice != "2" && choice != "1");

					if(choice == "2") {
						return 0;
					} 
				} else {
					system("cls");
					cout << "=============================================" << endl;
					if(username.length() == 8) {
						cout << setw(25) << left << "BUU PROMPT"  << setw(20) << right << "For Student" << endl;
					} else {
						cout << setw(25) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;
					}
					cout << "\nID: " << username << endl;
					cout << "Name: " << people.covertName(username) << endl;
					cout << "=============================================" << endl;
					cout << "Vaccinated : " << people.getVaccineName(username) << endl;
					cout << "Status : " << people.getStatus(username) << endl;
					cout << "Date#1 : " << people.getDate1(username) << endl;
					cout << "Date#2 : " << people.getDate2(username) << endl;
					cout << "Location : " << people.getLocation(username) << endl;
					cout << "=============================================" << endl;
					cout << "1. Go back" << endl;
					cout << "2. Exit" << endl; 
					cout << "=============================================" << endl;
					do {
						cout << "Enter menu: ";
						cin >> choice;
					} while(choice != "2" && choice != "1");
	
					if(choice == "2") {
						return 0;
					} 
			}
			
			} else if(mainMenu == "2") {
				if(username.length() == 8) {
					choice = "1";
				} else {
					string searchAgain;
					do {
						string searchName;
						system("cls");
						cout << "=============================================" << endl;
						if(username.length() == 8) {
							cout << setw(25) << left << "BUU PROMPT"  << setw(20) << right << "For Student" << endl;
						} else {
							cout << setw(25) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;
						}
						cout << "\nID: " << username << endl;
						cout << "Name: " << people.covertName(username) << endl;
						cout << "=============================================" << endl;
						cout << "Search Name: ";
						getchar();
						getline(cin,searchName);
						people.showPersonalInfo(searchName);
						cout << "=============================================" << endl;
						cout << "1. Search Again" << endl;
						cout << "2. Go Back" << endl;
						cout << "=============================================" << endl;
						cout << "Enter Menu: ";
						cin >> searchAgain;
						if(searchAgain == "2") {
							choice = "1";
						}
					} while(searchAgain == "1");
				}

			} else if(mainMenu == "3") {	
				choice = "0";
			} else if(mainMenu == "4") {	
				return 0; // exit program
			}

		} while(choice == "1");
		
	} while(mainMenu == "3");
	
		
	
	return 0;
	
}
