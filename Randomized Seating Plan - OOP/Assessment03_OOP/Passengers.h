#pragma once
#include "People.h"

class Passengers : public People {

public:
	Passengers();

	void Boarding(string pass);
	void Leaving(string pass);
	void setPassengers(ifstream& fin, ofstream& fout);
	void resetFile(ofstream& fout);
	void resetData();
	void DisplayAllocationOrReset(ofstream& fout);
};
