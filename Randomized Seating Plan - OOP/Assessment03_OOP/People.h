#pragma once

#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class People {
private:
	string arr[32];

public: 
	People();
	
	int randomizeF();
	int randomizeM();
	string getArr(int i);
	void setArr(int i, string s);
	virtual void Boarding(string pass) = 0;
	virtual void Leaving(string pass) = 0;
	virtual void setPassengers(ifstream& fin, ofstream& fout) = 0;
	virtual void resetFile(ofstream& fout) = 0;
	virtual void resetData() = 0;
	virtual void DisplayAllocationOrReset(ofstream& fout) = 0;
};
