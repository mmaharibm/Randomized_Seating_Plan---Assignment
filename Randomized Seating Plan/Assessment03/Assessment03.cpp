#include <iostream>
#include<string>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

int randomizeF(string arr[]) { //Randomly generates value of seat from women's and family section
	int i = rand() % 16;
	while (arr[i] != "0") {
		i = rand() % 16;
	}
	return i;
}

int randomizeM(string arr[]) { //Randomly generates value of seat from men's section
	int i = (rand() % (32 - 16)) + 16;
	while (arr[i] != "0") {
		i = (rand() % (32 - 16)) + 16;
	}
	return i;
}

void Boarding(string arr[], string board) {  //Allocates seat for a passenger
	int i{ 0 }, count{ 0 };	
	if (board == "L") {
		i = randomizeF(arr);				//for ladies and families the randomizeF() function is used
		arr[i] = "L";
	}
	else if (board == "F") {
		i = randomizeF(arr);
		arr[i] = "Mo";
		for (int j = 0; j < 2; j++) {
			i = randomizeF(arr);
			while (i == 3 || i == 15) {
				i = randomizeF(arr);
			}
			arr[i] = "C";
		}
	}
	else if (board == "M") {			// for males the randomizerM() function is used
		i = randomizeM(arr);
		arr[i] = "M";
	}
	else if (board == "MT") {					// for teen males. considering that they are males,	
			for (int j = 16; j < 32; j++) {		// if there is space in the males section they are seated there first
				if (arr[j] == "0") {			// else they are seated in the ladies' and family section as they are not much older
					count++;					// than children
				}
			}
			if (count > 0) {
				i = randomizeM(arr);
				arr[i] = "MT";
			}
			else {
				i = randomizeF(arr);
				arr[i] = "MT";
			}
	}
}

void Leaving(string arr[], string alight) {  // This function removes a passenger from the seat allocation when they leave the bus
	if (alight == "L") {
		for (int j = 0; j < 16; j++) {
			if (arr[j] == "L") {
				arr[j] = "0";
				return;
			}
		}
	}
	else if (alight == "F") {
		for (int j = 0; j < 16; j++) {
			if (arr[j] == "Mo") {
				arr[j] = "0";
				break;
			}
		}
		for (int j = 0; j < 16; j++) {
			if (arr[j] == "C") {
				arr[j] = "0";
				break;
			}
		}
		for (int j = 0; j < 16; j++) {
			if (arr[j] == "C") {
				arr[j] = "0";
				return;
			}
		}
		
	}
	else if (alight == "M") {
		for (int j = 16; j < 32; j++) {
			if (arr[j] == "M") {
				arr[j] = "0";
				return;
			}
		}
	}
	else if (alight == "MT") {
		for (int j = 16; j < 32; j++) {
			if (arr[j] == "MT") {
				arr[j] = "0";
				return;
			}
		}
	}
   
}

void allocateSeats(string arr[], ifstream &fin, ofstream &fout) { // this function reads from the passenger data file
	string action, passenger;									  // and allocate passenger seats for all stops in order
	int passCount = 0, x, stops{ 0 };							// removing passengers first
	fin >> stops;												// also adds stop data to stop data file so seating plan												
	for (int i = 0; i < stops; i++) {							// for every stop is stored
		fin >> action;											// for every stop is stored
		while (action != "/") {
			if (action == "Leave:") {
				fin >> action;
				while (action != "Board:") {
					passCount = (int)action[0] - '0';
					x = action.size();
					if (x == 3) {
						for (int i = 1; i < 3; i++) {
							passenger += action[i];
						}
					}
					else { passenger = action[1]; }
					for (int i = 0; i < passCount; i++) {
						Leaving(arr, passenger);
					}
					passenger.clear();
					fin >> action;
				}
			}
			if (action == "Board:") {
				while (true) {
					fin >> action;
					passCount = (int)action[0] - '0';
					x = action.size();
					if (x == 3) {
						for (int i = 1; i < 3; i++) {
							passenger += action[i];
						}
					}
					else { passenger = action[1]; }
					for (int i = 0; i < passCount; i++) {
						Boarding(arr, passenger);
					}
					passenger.clear();
					if (action == "/") {
						break;
					}
				}
			}
			fout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 C = Child), MT = Male Teen\n\n";
			fout << setw(20) << "DOOR\n\n";
			int count = 0, count2 = 0;
			for (int i = 0; i < 32; i++) {
				count++;
				count2++;
				if (arr[i].size() == 2) {
					fout << arr[i] << "  ";
				}
				else {
					fout << arr[i] << "   ";
				}
				if (count == 2) { fout << "    "; }
				else if (count == 4) {
					fout << endl;
					count = 0;
				}
				if (count2 == 16) {
					fout << endl << setw(20) << "DOOR\n" << endl;
					count2 = 0;
				}
			}
			fout << "\n-----------------------------------\n";
		}
	}															
}

void ResetFile(string arr[], ofstream& fout) { //this function resets the stop data file when the admin calls to reset seating plan
	fout.open("StopData.txt");
	fout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 C = Child), MT = Male Teen\n\n";
	fout << setw(20) << "DOOR\n\n";
	int count = 0, count2 = 0;
	for (int i = 0; i < 32; i++) {
		count++;
		count2++;
		if (arr[i].size() == 2) {
			fout << arr[i] << "  ";
		}
		else {
			fout << arr[i] << "   ";
		}
		if (count == 2) { fout << "    "; }
		else if (count == 4) {
			fout << endl;
			count = 0;
		}
		if (count2 == 16) {
			fout << endl << setw(20) << "DOOR\n" << endl;
			count2 = 0;
		}
	}
	fout << "\n-----------------------------------\n";
	fout.close();
}


void DisplayAllocationOrReset(string arr[], ofstream &fout) {
	int x;
	cout << "Press 'D' for Seat Allocation, Alternatively, Press 'R' to reset seating plan nad Display Default Plan \n\n";
	x=_getch();
	while (x != 100 && x != 114 ) {							// This function uses _getch() to read key stroke
		cout << "Please Press 'D' or 'R'\n";				// if D is pressed the if statement is ignored and the seating
		x=_getch();											// plan is printed
	}														// else if R is pressed the seating plan and text file are reset
															// and a default seating plan is printed
	if (x == 114) {
		for (int i = 0; i < 32; i++) {
			arr[i] = "0";
		}
		ResetFile(arr, fout);
		cout << "Seating Plan Reset to Default\n\n";
	}

	cout << "Displaying Allocation after Final Stop\n\n";
	cout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 C = Child), MT = Male Teen\n\n";
	int count = 0, count2 = 0;
	cout << setw(20) << "DOOR\n\n";
	for (int i = 0; i < 32; i++) {
		count++;
		count2++;
		if (arr[i].size() == 2) {
			cout << arr[i] << "  ";
		}
		else {
			cout << arr[i] << "   ";
		}
		if (count == 2) { cout << "    "; }
		else if (count == 4) {
			cout << endl;
			count = 0;
		}
		if (count2 == 16) {
			cout << endl << setw(20) << "DOOR\n" << endl;
			count2 = 0;
		}
	}
}
int main()
{
	

	ifstream fin;
	fin.open("PassengerData.txt");
	ofstream fout("StopData.txt");

	string passengers[32];

	for (int i = 0; i < 32; i++) {
		passengers[i] = "0";
	}

	allocateSeats(passengers, fin, fout);
	fin.close();
	fout.close();

	DisplayAllocationOrReset(passengers, fout);  //gives option to print plan or reset
	return 0;
}


