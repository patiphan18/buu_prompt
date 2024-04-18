#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

class Node {
	public:
		string number;
		string vaccineName;
		int amount;
		Node *link;
		Node(string number, string vaccineName, int amount) {
			this->number = number;
			this->vaccineName = vaccineName;
			this->amount = amount;
		}
};

class LinkedList {
	private:
		Node *head;
		Node *tail;
		int count;
	public:
		LinkedList() {
			this->head = NULL;
			this->tail = NULL;
			count = 0;
		}
		
		void add(string number, string vaccineName, int amount) {
			Node *temp = new Node(number, vaccineName, amount);
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
		
		void insert(int index, string number, string vaccineName, int amount) {
			if(index < 0 || index > count) {
				return;	
			}	
				
			if(index == 0) {
				Node *temp = new Node(number, vaccineName, amount);
				temp->link = head;
				head = temp;
				count++;
			} else if(index == count) {
				LinkedList::add(number, vaccineName, amount);
			} else {
				Node *temp = new Node(number, vaccineName, amount);
				Node *ptemp = head;
				for(int i=0; i<index-1; i++) {
					ptemp = ptemp->link;
				}
				temp->link = ptemp->link;
				ptemp->link = temp;
				count++;
			}
		}
		
		void addRead() {
			fstream readFile;
			readFile.open("vaccine.txt", ios::in);
			string line;
			string readNumber;
			int readAmount;
			if (!readFile) {
				cout << "File not found!" << endl;
			}
			else {
				while( getline(readFile, line) ) {
					readNumber = line.substr(0, line.find(","));
					line.erase(0, line.find(",")+1);
					stringstream streamAmount(line.substr(line.find(",")+1, line.length() - line.find(",") ) );
					streamAmount >> readAmount;
					LinkedList::add(readNumber, line.substr(0,line.find(",")), readAmount);
				}
			}
	
			readFile.close();
		}
				
//		void remove(int number, string vaccineName, int amount) {
//			Node *ptemp = head;
//			Node *temp = head;
//			int index = -1;
//			for(int i=0; i<count; i++) {
//				if(temp->data == data) {
//					index = i;
//					break;
//				}
//				ptemp = temp;
//				temp = temp->link;
//			}
//			
//			if(index == -1) {
//				return;
//			} else if(index == 0) {
//				head = head->link;
//				delete temp;
//			} else if(index == count-1) {
//				ptemp->link = NULL;
//				delete temp;
//			} else {
//				ptemp->link = temp->link;
//				delete temp;
//			}
//			count--;
//		}
		
		void show() {
			if(head == NULL) {
				cout << "No data" << endl;
				return;
			}
			Node *temp = head;
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
		
		~LinkedList() {
			for(int i=0; i<count; i++){
				Node *temp = head;
				head = head->link;
				delete temp;
				temp = NULL;
			}
			head = NULL;
			tail = NULL;
		}
		
};

int main() {
	LinkedList obj;
	obj.addRead();
	
	obj.show();
	return 0;
}
