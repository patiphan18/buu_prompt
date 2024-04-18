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
			cout << "=========================================================" << endl;
			cout << setw(8) << left << "   No." 
				<< setw(25) << left << "Vaccine" 
				<< setw(15) << left << "Amount" 
				<< "Remain" << endl;
			cout << "=========================================================" << endl;
			for(int i=0; i<count; i++) {
				cout << setw(8) << left << "   " + temp->number + "."
					<< setw(25) << left << temp->vaccineName
					<< setw(5) << left << temp->amount << setw(10) << left << "Dose" 
					<< setw(3) << left << temp->remain << " Dose" << endl;
					
				stringstream streamAmount(temp->amount);
				streamAmount >> numAmount;
				stringstream streamRemain(temp->remain);
				streamRemain >> numRemain;
				totalAmount += numAmount;
				totalRemain += numRemain;
				temp = temp->link;
			}
			cout << "=========================================================" << endl;
			ostringstream ssTotalAmount;
     		ssTotalAmount << totalAmount;
     		string strTotalAmount = ssTotalAmount.str();
			cout << setw(33) << left << "   Total" 
			<< setw(15) << left << strTotalAmount + "  Dose" 
			<< totalRemain << " Dose" << endl;
			cout << "=========================================================" << endl;
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


class NodePeople {
	public:
		string id;
		string password;
		string name;
		string vaccineType;
		string acceptDose;
		string date1;
		string date2;
		NodePeople *link;
		NodePeople(string id, string password, string name, string vaccineType, string acceptDose, string date1, string date2) {
			this->id = id;
			this->password = password;
			this->name = name;
			this->vaccineType = vaccineType;
			this->acceptDose = acceptDose;
			this->date1 = date1;
			this->date2 = date2;
		}
};

class People {
	private:
		Vaccine vaccine;
		NodePeople *head;
		NodePeople *tail;
		int count;
	public:
		People() {
			this->head = NULL;
			this->tail = NULL;
			count = 0;
		}
		
		void add(string id, string password, string name, string vaccineType, string acceptDose, string date1, string date2) {
			NodePeople *temp = new NodePeople(id, password, name, vaccineType, acceptDose, date1, date2);
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
			fstream readFile;
			readFile.open("people.txt", ios::in);
			string line;
			string readId, readPassword, readName, readVaccineType, readAcceptDose, readDate1, readDate2;
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
					readDate2 = line;
					
					People::add(readId, readPassword, readName, readVaccineType, readAcceptDose, readDate1, readDate2);
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
			cout << "===============================================================================================================" << endl;
			cout << setw(8) << left << "   NO." 
				<< setw(15) << left << "Student ID" 
				<< setw(20) << left << "Name" 
				<< setw(20) << left << "Vaccinated" 
				<< setw(15) << left << "Status" 
				<< setw(15) << left << "Date#1" 
				<< "Date#2" << endl;
			cout << "===============================================================================================================" << endl;		
			for(int i=1; i<=count; i++) {
				ostringstream ss;
     			ss << i;
     			string strNo = ss.str();
				cout << setw(8) << left << "   " + strNo + "."
					<< setw(15) << left << temp->id
					<< setw(20) << left << temp->name.substr(0, 1) + ". " + temp->name.substr(temp->name.find(" ")+1, temp->name.length()-1);
					if(temp->vaccineType == "0") {
							cout << setw(20) << left << "Not Vaccinated" 
								<< setw(15) << left << "-"
								<< setw(15) << left << temp->date1 
								<< temp->date2 << endl;
					} else {
						cout << setw(20) << left << vaccine.getVaccineName(temp->vaccineType) 
							<< setw(15) << left << temp->acceptDose + "/" + vaccine.getMaxDose(temp->vaccineType); 
							if(temp->date1 != "-") {
								int year1;
								stringstream streamYear1(temp->date1.substr(6, 4));
								streamYear1 >> year1;
								ostringstream ssYear1;
								ssYear1 << year1 + 543;
								string strYear1 = ssYear1.str();
								cout << setw(15) << left << temp->date1.substr(0, 6) + strYear1;
							} else {
								cout << setw(15) << left << temp->date1;
							} 
							if(temp->date2 != "-") {
								int year2;
								stringstream streamYear2(temp->date2.substr(6, 4));
								streamYear2 >> year2;
								ostringstream ssYear2;
								ssYear2 << year2 + 543;
								string strYear2 = ssYear2.str();
								cout << temp->date2.substr(0, 6) + strYear2 << endl;
							} else {
								cout << temp->date2 << endl;
							} 			
					}
				temp = temp->link;
			}
			cout << "===============================================================================================================" << endl;
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
		
		string getFirstName(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					return temp->name.substr(0, temp->name.find(" "));
				
				temp = temp->link;
			}
			return "-";
		}
		
		string getLastName(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count ;i++) {
				if(username == temp->id) 
					return temp->name.substr(temp->name.find(" ")+1, temp->name.length()-temp->name.find(" "));
				
				temp = temp->link;
			}
			return "-";
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

class Menu {
	private:
		People people;
		string id;
	public:
		void show() {	
			int userMenu, homeMenu;
			int loginCheck = 0;		
			do{
				system("cls");
				//cout << "failed to login" << endl;
				cout << "============================" << endl;
				cout << "BUU PROMPT" << endl;
				cout << "============================" << endl;
				if(loginCheck == 2) {
					cout << "Wrong password" << endl;
				} else if(loginCheck == 3) {
					cout << "Not found this user" << endl;
				}
				cout << "  1.Log in" << endl;
				cout << "  2.Exit" << endl; 
				cout << "============================" << endl;
				cout << "  Enter menu: ";
				cin >> homeMenu;
				if(homeMenu == 1) {
					loginCheck = login();
					if(loginCheck == 1) { // login success		
						userMenu = mainMenu(); 
					}
				} else {
					return; // exit program
				}
				
			}while(loginCheck == 2 || loginCheck == 3 || userMenu == 2);
			
		}
		
		int login() {
			string username, password;
			people.addRead();
					
			cout << "============================" << endl;
			cout << "BUU PROMPT" << endl;
			cout << "LOGIN" << endl;
			cout << "============================" << endl;
			cout << "ID : ";
			cin >> username;
			cout << "Password : ";
			cin >> password;
			this->id = username;
			return people.checkLogin(username, password);
		}
		
		int mainMenu() {
			int menu;
			cout << "===================================" << endl;
			if(id.length() == 8) {
				cout << setw(15) << left << "BUU PROMPT"  << setw(20) << right << "For Student" << endl;
			} else {
				cout << setw(15) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;
			}
			cout << setw(15) << left << " " 
				<< setw(20) << right << "Name: " + people.getFirstName(id).substr(0,1) + ". " + people.getLastName(id) 
				<< " " << endl;
			cout << "===================================" << endl;
			cout << "1.See booking history (coming soon)" << endl;
			cout << "2.Go back" << endl;
			cout << "3.Exit" << endl; 
			cout << "===================================" << endl;
			cout << "Enter menu: ";
			cin >> menu;
			return menu;
		}
};

int main() {
	Menu menu;
	menu.show();
	return 0;
}
