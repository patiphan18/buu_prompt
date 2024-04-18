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
		string name;
		string vaccineType;
		string acceptDose;
		string date1;
		string date2;
		NodePeople *link;
		NodePeople(string id, string name, string vaccineType, string acceptDose, string date1, string date2) {
			this->id = id;
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
		
		void add(string id, string name, string vaccineType, string acceptDose, string date1, string date2) {
			NodePeople *temp = new NodePeople(id, name, vaccineType, acceptDose, date1, date2);
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
			string readId, readName, readVaccineType, readAcceptDose, readDate1, readDate2;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readId = line.substr(0, line.find(","));
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
					
					People::add(readId, readName, readVaccineType, readAcceptDose, readDate1, readDate2);
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
		Vaccine vaccine;
		People people;
	public:
		void show() {
			int menu;
			cout << "============================" << endl;
			cout << "BUU PROMPT" << endl;
			cout << "============================" << endl;
			cout << "1.See Vaccine" << endl;
			cout << "2.See People" << endl; 
			cout << "============================" << endl;
			cout << "Enter menu: ";
			cin >> menu;
			if(menu == 1) {
				vaccine.addRead();
				vaccine.show();
			} else if(menu == 2) {
				people.addRead();
				people.show();
			}
		}
};

int main() {
	Menu menu;
	menu.show();
	return 0;
}
