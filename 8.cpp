#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <conio.h>

using namespace std;

int stringToNumber(string str) {
	int number;
	stringstream ss(str);
	ss >> number;
	return number;
}

string numberToString(int num) {
	ostringstream os;
	os << num;
	string str = os.str();
	return str;
}

bool isNumber(string str) {
    for(int i=0; i<str.length(); i++) {
        if(isdigit(str[i]) == 0) 
			return false;
    }
    return true;
}

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
			} else {
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
		
		int getRemain(string vaccineType) {
			NodeVaccine *temp = head;
			for(int i=1; i<=count; i++) {
				if(temp->number == vaccineType) 
					return stringToNumber(temp->remain);
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
					
				numAmount = stringToNumber(temp->amount);
				numRemain = stringToNumber(temp->remain);
				totalAmount += numAmount;
				totalRemain += numRemain;
				temp = temp->link;
			}
			cout << "===========================================================" << endl;
     		string strTotalAmount = numberToString(totalAmount);
			cout << setw(33) << left << "   Total" 
				<< setw(5) << left << strTotalAmount << setw(10) << left << "Dose" 
				<< setw(5) << left << totalRemain << "Dose" << endl;
			cout << "===========================================================" << endl;
		}
		
		bool updateAmount(string id, string amount) {
			if(isNumber(amount) == false)
				return false;
				
			int newAmount = stringToNumber(amount);
			
			if(newAmount < 1) {
				return false;
			}
			NodeVaccine *temp = head;
			while(temp != NULL) {
				if(temp->number == id) {
					int numAmount = stringToNumber(temp->amount);
					numAmount += newAmount;
					temp->amount = numberToString(numAmount);
					
					int numRemain = stringToNumber(temp->remain);
					numRemain += newAmount;
					temp->remain = numberToString(numRemain);
     				
     				ofstream updateFile("vaccine.txt");
     				temp = head;
     				for(int i=0; i<count; i++) {
     					updateFile << temp->number << "," << temp->vaccineName << ","
							<< temp->maxDose << "," << temp->amount << "," << temp->remain << "\n";
						
     					temp = temp->link;	
					}
					updateFile.close();
					return true;
				}
				temp = temp->link;
			}
			return false;
		}
		
		bool addNewVaccine(string id, string name, string maxDose, string amount) {
			if(isNumber(amount) == false || isNumber(maxDose) == false || isNumber(id) == false) {
				return false;
			}
						
			int numAmount = stringToNumber(amount);
			int numMaxDose = stringToNumber(maxDose);
		
			if(numAmount < 1 || numMaxDose < 1) {
				return false;
			}
			NodeVaccine *temp = head;
			while(temp != NULL) {
				if(temp->number == id || temp->vaccineName == name) {
					return false;
				}
				temp = temp->link;
			}
			Vaccine::add(id, name, amount, maxDose, amount);
     		Vaccine::sortAscendingById();
     		ofstream updateFile("vaccine.txt");
     		temp = head;
     		for(int i=0; i<count; i++) {
     			updateFile << temp->number << "," << temp->vaccineName << ","
					<< temp->maxDose << "," << temp->amount << "," << temp->remain << "\n";
						
     			temp = temp->link;	
			}
			updateFile.close();
			return true;
		}
		
		void sortAscendingById() {
			NodeVaccine *temp = NULL;
			for(int i=0; i<count; i++) {
				temp = head;
				
				for(int j=0; j<count-i-1; j++) {
					int currentId = stringToNumber(temp->number);
					int nextId = stringToNumber(temp->link->number);
					if(currentId > nextId) {
						swapData(temp);
					} // swap data
					
					temp = temp->link;
				} // for j
				
			} // for i
		}
		
		void swapData(NodeVaccine *temp) {	
			NodeVaccine *nextNode = temp->link;
			NodeVaccine *currentNode = new NodeVaccine(temp->number, temp->vaccineName, temp->amount, temp->maxDose, temp->remain);
			currentNode->link = temp->link->link;
			if(tail == nextNode)
				tail = currentNode;
			
			temp->number = temp->link->number;
			temp->vaccineName = temp->link->vaccineName;
			temp->maxDose = temp->link->maxDose;
			temp->amount = temp->link->amount;
			temp->remain = temp->link->remain;
			
			temp->link = currentNode;
			delete nextNode;
		}
		
		void showForBookking() {
			NodeVaccine *temp = head;
			cout << left << setw(5) << "No."
				<< left << setw(20) << "Vaccine"
				<< "Remain" << endl;
			while(temp != NULL) {
				cout << left << setw(5) << temp->number + "."
				<< left << setw(20) << temp->vaccineName
				<< left << setw(4) << temp->remain << "Dose" << endl; 
				temp = temp->link;
			}
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
			} else {
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
		
		void show() {
			NodeHospital *temp = head;
			cout << "===========================================" << endl;
			cout << left << setw(5) << "No." << "Location" << endl;
			cout << "===========================================" << endl;
			while(temp != NULL) {				
				cout << left << setw(5) << temp->hospitalId + "." << temp->hospitalName << endl;
				temp = temp->link;
			}
			cout << "===========================================" << endl;
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
			} else {
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
			int i = 1;
			while(temp != NULL) {
				if(temp->id.length() == 8) {
     				string strNo = numberToString(i);
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
					i++;
				}
				temp = temp->link;
				
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
			for(int i=0; i<count; i++) {
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
			for(int i=0; i<count; i++) {
				if(username == temp->id) 
					break;
				
				temp = temp->link;
			}
			if(temp->date1 != "-") {
				int year1 = stringToNumber(temp->date1.substr(6, 4));
				string strYear1 = numberToString(year1+543);
				string month = convertMonth(temp->date1.substr(3, 2));
				
				return temp->date1.substr(0, 2) + " " + month + " " + strYear1;
			} else {
				return temp->date1;
			} 
						
		}
		
		string getDate2(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count; i++) {
				if(username == temp->id) 
					break;
				
				temp = temp->link;
			}
			if(temp->date2 != "-") {
				int year2 = stringToNumber(temp->date2.substr(6, 4));
				string strYear2 = numberToString(year2 + 543);
				string month = convertMonth(temp->date2.substr(3, 2));
				
				return temp->date2.substr(0, 2) + " " + month + " " + strYear2;
			} else {
				return temp->date2;
			} 
						
		}
		
		string convertMonth(string month) {
			string monthList[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};	
			int index = stringToNumber(month);
			return monthList[index-1];
		}
		
		string getLocation(string username) {
			NodePeople *temp = head;
			for(int i=0; i<count; i++) {
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
			for(int i=0; i<count; i++) {
				if(searchName == temp->name) {
					find = 1;
					cout << "---------------------------------------------" << endl;
					cout << "ID: " << temp->id << endl;
					cout << "Name: " << People::covertName(temp->id) << endl;
					cout << "---------------------------------------------" << endl;
					cout << "Vaccinated : " << People::getVaccineName(temp->id) << endl;
					cout << "Status : " << People::getStatus(temp->id) << endl;
					cout << "Date#1 : " << People::getDate1(temp->id) << endl;
					cout << "Date#2 : " << People::getDate2(temp->id) << endl;
					cout << "Location : " << People::getLocation(temp->id) << endl;
				}
				temp = temp->link;
			}
			if(find == 0) {
				cout << "\n\t\t!! Not Found !!\n" << endl;
			}

		}
		
		void sortAscendingByName() {
			NodePeople *temp = NULL;
			for(int i=0; i<count; i++) {
				temp = head;
				
				for(int j=0; j<count-i-1; j++) {
	
					if(temp->name > temp->link->name) {
						swapData(temp);
					} // swap data
					
					temp = temp->link;
					
				} // for j
				
			} // for i
		}
		
		void sortDescendingByName() {
			NodePeople *temp = NULL;

			for(int i=0; i<count; i++) {
				temp = head;
				
				for(int j=0; j<count-i-1; j++) {
	
					if(temp->name < temp->link->name) {
						swapData(temp);
					} // swap data
					
					temp = temp->link;
					
				} // for j
				
			} // for i
		}
		
		void sortAscendingById() {
			NodePeople *temp = NULL;
			for(int i=0; i<count; i++) {
				temp = head;
				
				for(int j=0; j<count-i-1; j++) {
	
					if(temp->id > temp->link->id) {
						swapData(temp);
					} // swap data
					
					temp = temp->link;
					
				} // for j
				
			} // for i
		}
		
		void sortDescendingById() {
			NodePeople *temp = NULL;
			for(int i=0; i<count; i++) {
				temp = head;
				
				for(int j=0; j<count-i-1; j++) {

					if(temp->id < temp->link->id) {
						swapData(temp);
					} // swap data
					
					temp = temp->link;
					
				} // for j
				
			} // for i
		}
		
		void swapData(NodePeople *temp) {	
			NodePeople *nextNode = temp->link;
			NodePeople *currentNode = new NodePeople(temp->id, temp->password, temp->name, temp->vaccineType, temp->acceptDose, temp->date1, temp->date2, temp->location);
			currentNode->link = temp->link->link;
			if(tail == nextNode)
				tail = currentNode;
			
			temp->id = temp->link->id;
			temp->password = temp->link->password;
			temp->name = temp->link->name;
			temp->vaccineType = temp->link->vaccineType;
			temp->acceptDose = temp->link->acceptDose;
			temp->date1 = temp->link->date1;
			temp->date2 = temp->link->date2;
			temp->location = temp->link->location;
			
			temp->link = currentNode;
			delete nextNode;
		}
		
		bool bookingVaccine(string username) {
			time_t now = time(0);
			tm *ltm = localtime(&now);
			string location, vaccineId, strDay, strMonth, strYear;
			int day, month, year;
			int dateCheck = 0;
			int remain, maxDose;
			do {
				system("cls");		
				hospital.show();
				cout << "Enter : ";
				cin >> location;
			} while(hospital.getHospitalName(location) == "-");
			
			do {
				system("cls");
				cout << "==========================================" << endl;
				cout << "Location : " << hospital.getHospitalName(location) << endl;
				cout << "==========================================" << endl;
				vaccine.showForBookking();
				cout << "==========================================" << endl;			
				cout << "Enter : ";
				cin >> vaccineId;
				if(vaccine.getVaccineName(vaccineId) != "Not Vaccinated") {
					remain = vaccine.getRemain(vaccineId);
					maxDose = stringToNumber( vaccine.getMaxDose(vaccineId) );
				}
			}while(vaccine.getVaccineName(vaccineId) == "Not Vaccinated" || remain < maxDose);
			
			do {
				system("cls");
				cout << "==========================================" << endl;
				cout << "Date to vaccinate" << endl;
				cout << "==========================================" << endl;	
				if(dateCheck == 1) {
					cout << "Invalid date, please choose date again" << endl;
				}	
				cout << "Enter date : ";
				cin >> strDay;
				if(isNumber(strDay) == false) {
					dateCheck = 1;
				} else {
					dateCheck = 0;
				}

				cout << "\nChoose month" << endl;
				cout << left << setw(5) << "1." << "January" << endl;
				cout << left << setw(5) << "2." << "February" << endl;
				cout << left << setw(5) << "3." << "March" << endl;
				cout << left << setw(5) << "4." << "April" << endl;
				cout << left << setw(5) << "5." << "May" << endl;
				cout << left << setw(5) << "6." << "June" << endl;
				cout << left << setw(5) << "7." << "July" << endl;
				cout << left << setw(5) << "8." << "August" << endl;
				cout << left << setw(5) << "9." << "September" << endl;
				cout << left << setw(5) << "10." << "October" << endl;
				cout << left << setw(5) << "11." << "November" << endl;
				cout << left << setw(5) << "12." << "December" << endl;
				cout << "Enter month : ";
				cin >> strMonth;
				if(isNumber(strMonth) == false) {
					dateCheck = 1;
				} else {
					dateCheck = 0;
				}
				
				cout << "\nChoose year" << endl;
				cout << "1. " << 1900 + ltm->tm_year << endl;
				cout << "2. " << 1900 + ltm->tm_year + 1 << endl;
				cout << "Enter year : ";
				cin >> strYear;
				
				if(strYear == "1") {
					year = 1900 + ltm->tm_year;
				} else if(strYear == "2") {
					year = (1900 + ltm->tm_year) + 1;
				} else {
					dateCheck = 1;
				}
				
				if(dateCheck != 1) {
					month = stringToNumber(strMonth);
					day = stringToNumber(strDay);
				} else {
					month = 0;
					day = 0;
					year = 0;
				}
				
				if(checkDateCorrect(day, month, year) == false) 
					dateCheck = 1;
					
			} while(checkDateCorrect(day, month, year) == false);
			
			system("cls");
			cout << "==========================================" << endl;
			cout << "\t\tSuccess" << endl;
			cout << "==========================================" << endl;
			getch();
		}
		
		bool checkDateCorrect(int day, int month, int year) {
			time_t now = time(0);
			tm *ltm = localtime(&now);
			if(year < (1900 + ltm->tm_year) ) {
				return false;
			} else if(year == (1900 + ltm->tm_year) ){
				if(month < (1 + ltm->tm_mon) ) {
					return false;
				} else if(month == (1 + ltm->tm_mon) ) {
					if(day <= ltm->tm_mday ) {
						return false;
					}
				}
			} 
			
         	if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
         		if(day > 0 && day <= 31) {
		 			return true;
				} else {
					return false;
				}
		 	} else if(month==4 || month==6 || month==9|| month==11) {
		 		if(day>0 && day<=30) {
		 			return true;
				} else {
					return false;
				}	
		 	} else if(month==2) {
               	if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29) {
               		return true;
				} else if(day>0 && day<=28) {
               		return true;;
			   	} else {
			   		return false;
			   	}
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
	string homeMenu; // before login
	string mainMenu; // after login
	string choice;
	int loginCheck;
	string username, password;

	homePage: // Home Menu Page
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
	cin >> homeMenu;
	// ----- End Home Menu -----
	if(homeMenu == "1") {
	cout << "============================" << endl;
	cout << "BUU PROMPT" << endl;
	cout << "LOGIN" << endl;
	cout << "============================" << endl;
//	cout << "ID : ";
//	cin >> username;
//	cout << "Password : ";
//	cin >> password;

	username = "63160052";
	password = "bscEVmCp"; 
	
//	username = "63160081";
//	password = "sknyzNtb";
	
//	username = "5815007867";
//	password = "a46zkEGq";
	loginCheck = people.checkLogin(username, password);
	if(loginCheck != 1)
		goto homePage;
	} else if(homeMenu == "2") {
		return 0; // exit program
	} else {
		goto homePage;
	}
	// ----- End Home Page -----
		
	mainMenuPage: // main menu page
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
		cout << "1.See vaccine stocks" << endl;
		cout << "2.See booking list" << endl;
		cout << "3.Search Name" << endl;
		cout << "4.Go back" << endl;
		cout << "5.Exit" << endl; 
		cout << "=============================================" << endl;
		cout << "Enter menu: ";
		cin >> mainMenu;
		
		if(mainMenu == "5") {
			return 0; 
		} else if(mainMenu == "4") {
			goto homePage;
		} else {
			goto mainMenuPage;
		}
			
	} else {
		if(people.getStatus(username) == "-") {
			cout << "1.Booking vaccine" << endl;
			cout << "2.See booking history" << endl;
			cout << "3.Go back" << endl;
			cout << "4.Exit" << endl;
			cout << "=============================================" << endl;
			cout << "Enter menu: ";
			cin >> mainMenu;
			if(mainMenu == "1") {
				mainMenu = "0";
			} else if(mainMenu == "2") {
				mainMenu = "1";
			} else if(mainMenu == "3") {
				goto homePage;
			} else if(mainMenu == "4") {
				return 0;
			} else {
				goto mainMenuPage;
			}
		} else {
			cout << "1.See booking history" << endl;
			cout << "2.Go back" << endl;
			cout << "3.Exit" << endl;
			cout << "=============================================" << endl;
			cout << "Enter menu: ";
			cin >> mainMenu;
			if(mainMenu == "1") {
				mainMenu = "1";
			} else if(mainMenu == "2") {
				goto homePage;
			} else if(mainMenu == "3") {
				return 0;
			} else {
				goto mainMenuPage;
			}
		}
	} 
	// ----- End Main Menu Page -----
		
	if(mainMenu == "0") {
		people.bookingVaccine(username);
	}
		
	if(mainMenu == "1") {
		if(username.length() == 10) {
			Vaccine vaccine;
			vaccine.addRead();
			string again = "2";
			vaccinePage: // Vaccine Page
			system("cls");
			vaccine.show();
			cout << "1.Add vaccine in stock" << endl;
			cout << "2.Add new vaccine" << endl;
			cout << "3.Go back" << endl;
			cout << "4.Exit" << endl;
			cout << "===========================================================" << endl;
			cout << "Enter menu: ";
			cin >> choice;
			// ----- End Vaccine Page -----
			if(choice == "4") {
				return 0; // Exit
			} else if(choice == "1") {							
				addAmount: // Add Amount Page
				again = "2";
				system("cls");
				vaccine.show();
				string id, amount;
				cout << "Add Vaccine ID: ";
				cin >> id;
				cout << "Number Of Vaccines: ";
				cin >> amount;
				// ----- End Add Amount Page -----
				bool checkUpdate = vaccine.updateAmount(id, amount);
				if(checkUpdate == false) {
					system("cls");
					vaccine.show();
					cout << "\n\t\t\t!! Error !!\n" << endl;
					cout << "===========================================================" << endl;
					do {
						cout << "Add Again (1.Yes/2.No): ";
						cin >> again;
					} while(again != "1" && again != "2");
					
					if(again == "1")
						goto addAmount;
				}				
				goto vaccinePage; 
							
			} else if(choice == "2") {
				addNewVaccine: // Add New Vaccine Page
				system("cls");
				vaccine.show();
				string id, name, amount, maxDose;
				cout << "New Vaccine ID: ";
				cin >> id;
				cout << "Vaccine Name: ";
				cin >> name;
				cout << "Dose Of Vaccines: ";
				cin >> maxDose;
				cout << "Number Of Vaccines: ";
				cin >> amount;
				// ----- End Add New Vaccine Page
				bool checkUpdate = vaccine.addNewVaccine(id, name, maxDose, amount);
				if(checkUpdate == false) {
					system("cls");
					vaccine.show();
					cout << "\n\t\t\t!! Error !!\n" << endl;
					cout << "===========================================================" << endl;
					do {
						cout << "Add Again (1.Yes/2.No): ";
						cin >> again;
					} while(again != "1" && again != "2");
					
					if(again == "1")
						goto addNewVaccine;
				}							
				goto vaccinePage;
					
			} else if(choice == "3"){
				goto mainMenuPage; // back to main menu page
			} else {
				goto vaccinePage;
			}
					
		} else {
			system("cls");
			cout << "=============================================" << endl;
			cout << setw(25) << left << "BUU PROMPT"  << setw(20) << right << "For Student" << endl;			
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
			} else {
				goto mainMenuPage;
			} 
		} // student
				
		} else if(mainMenu == "2") {
			if(username.length() == 8) {
				goto mainMenuPage;
			} else {
				bookingListPage:
				system("cls");
				cout << "=============================================" << endl;
				cout << setw(25) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;
				cout << "\nID: " << username << endl;
				cout << "Name: " << people.covertName(username) << endl;
				cout << "=============================================" << endl;
				cout << "1.A-Z By Name" << endl;
				cout << "2.Z-A By Name" << endl;
				cout << "3.Ascending by Student ID" << endl;
				cout << "4.Descending by Student ID" << endl;
				cout << "5.Go Back" << endl;  
				cout << "=============================================" << endl;
				cout << "Enter menu: ";
				cin >> choice;
				if(choice == "1") {
					people.sortAscendingByName();
				} else if(choice == "2") {
					people.sortDescendingByName();
				} else if(choice == "3") {
					people.sortAscendingById();
				} else if(choice == "4") {
					people.sortDescendingById();
				} else if(choice =="5") {
					goto mainMenuPage;
				} else {
					goto bookingListPage;
				}
					
				people.show();
				cout << "1. Go back" << endl;
				cout << "2. Exit" << endl; 
				do {
					cout << "Enter menu: ";
					cin >> choice;
				} while(choice != "2" && choice != "1");

				if(choice == "2") {
					return 0;
				} else {
					goto bookingListPage;
				} 
			} // doctor
		
		} else if(mainMenu == "3") {
			if(username.length() == 8) {
				goto mainMenuPage;
			} else {
				string searchAgain;
				searchNamePage:
				string searchName;
				system("cls");
				cout << "=============================================" << endl;
				cout << setw(25) << left << "BUU PROMPT" << setw(20) << right << "For Doctor" << endl;	
				cout << "\nID: " << username << endl;
				cout << "Name: " << people.covertName(username) << endl;
				cout << "=============================================" << endl;
				cout << "Search Name: ";
				getchar();
				getline(cin, searchName);
				people.showPersonalInfo(searchName);
				cout << "=============================================" << endl;
				cout << "1. Search Again" << endl;
				cout << "2. Go Back" << endl;
				cout << "=============================================" << endl;
				do {
					cout << "Enter Menu: ";
					cin >> searchAgain;
				} while(searchAgain != "1" && searchAgain != "2");
				
				if(searchAgain == "1") {
					goto searchNamePage;
				} else {
					goto mainMenuPage;
				} 
				
			} // doctor
		} else {
			goto mainMenuPage;
		}

	return 0;
}
