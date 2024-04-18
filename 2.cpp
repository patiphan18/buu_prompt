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
		int amount;
		string maxDose;
		NodeVaccine *link;
		NodeVaccine(string number, string vaccineName, int amount, string maxDose) {
			this->number = number;
			this->vaccineName = vaccineName;
			this->amount = amount;
			this->maxDose = maxDose;
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
		
		void add(string number, string vaccineName, int amount, string maxDose) {
			NodeVaccine *temp = new NodeVaccine(number, vaccineName, amount, maxDose);
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
			string readNumber, readVaccineName, readStrAmount;
			int readAmount;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readNumber = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readVaccineName = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					readStrAmount = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					stringstream streamAmount(readStrAmount);
					streamAmount >> readAmount;
					Vaccine::add(readNumber, readVaccineName, readAmount, line);
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
			int total = 0;
			cout << "===================================================" << endl;
			cout << "BUU PROMPT" << endl;
			cout << "===================================================" << endl;
			cout << setw(8) << left << "No." 
				<< setw(25) << left << "Vaccine" << "Amount" << endl;
			cout << "===================================================" << endl;
			for(int i=0; i<count; i++) {
				cout << setw(8) << left << temp->number + "."
					<< setw(25) << left << temp->vaccineName
					<< left << temp->amount << " Dose" << endl;
				total += temp->amount;
				temp = temp->link;
			}
			cout << "===================================================" << endl;
			cout << setw(32) << left << "Total" << total << " Dose" << endl;
			cout << "===================================================" << endl;
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
		int acceptDose;
		NodePeople *link;
		NodePeople(string id, string name, string vaccineType, int acceptDose) {
			this->id = id;
			this->name = name;
			this->vaccineType = vaccineType;
			this->acceptDose = acceptDose;
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
		
		void add(string id, string name, string vaccineType, int acceptDose) {
			NodePeople *temp = new NodePeople(id, name, vaccineType, acceptDose);
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
			string readId, readName, readVaccineType;
			int readAcceptDose;
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
					stringstream streamAcceptDose(line);
					streamAcceptDose >> readAcceptDose;
					People::add(readId, readName, readVaccineType, readAcceptDose);
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
			cout << "=======================================================================" << endl;
			cout << "BUU PROMPT" << endl;
			cout << "=======================================================================" << endl;
			cout << setw(8) << left << "No." 
				<< setw(25) << left << "Name" 
				<< setw(25) << left << "Vaccinated" 
				<< "Status" << endl;
			cout << "=======================================================================" << endl;
			for(int i=1; i<=count; i++) {
				ostringstream ss;
     			ss << i;
     			string strNo = ss.str();
				cout << setw(8) << left << strNo + "."
					<< setw(25) << left << temp->name;
					if(temp->vaccineType == "0") {
							cout << setw(25) << left << "Not Vaccinated" << "-" << endl;
					} else {
						cout << setw(25) << left << vaccine.getVaccineName(temp->vaccineType) 
							<< temp->acceptDose << "/" << vaccine.getMaxDose(temp->vaccineType) << endl;
					}
				temp = temp->link;
			}
			cout << "=======================================================================" << endl;
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
	People obj;
	obj.addRead();
	
	obj.show();
	return 0;
}
