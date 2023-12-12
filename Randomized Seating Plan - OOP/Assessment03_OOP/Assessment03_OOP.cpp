#include <iostream>
#include "People.h"
#include "Passengers.h"

using namespace std;
int main()
{
    ifstream fin;
    fin.open("PassengerData.txt");
    ofstream fout("StopData.txt");

    Passengers p;
    p.setPassengers(fin, fout);
    
    fin.close();
    fout.close();

    p.DisplayAllocationOrReset(fout);

    return 0;
}
