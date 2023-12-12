#include "Passengers.h"

Passengers::Passengers() : People() {}


void Passengers::Boarding(string pass) { // Allocates seat for a passenger
    int i{ 0 }, count{ 0 };
    if (pass == "L") {
        i = randomizeF(); // for ladies and families the randomizeF() function is used
        setArr(i, "L");
    }
    else if (pass == "F") {
        i = randomizeF();
        setArr(i, "Mo");
        for (int j = 0; j < 2; j++) {
            i = randomizeF();
            while (i == 3 || i == 15) {
                i = randomizeF();
            }
            setArr(i, "C");
        }
    }
    else if (pass == "M") { // for males the randomizerM() function is used
        i = randomizeM();
        setArr(i, "M");
    }
    else if (pass =="MT") {             // for teen males. considering that they are males,
        for (int j = 16; j < 32; j++) { // if there is space in the males section
                                        // they are seated there first
            if (getArr(j) == "0") {        // else they are seated in the ladies' and family
                                        // section as they are not much older
                count++;                // than children
            }
        }
        if (count > 0) {
            i = randomizeM();
            setArr(i, "MT");
        }
        else {
            i = randomizeF();
            setArr(i, "MT");
        }
    }
}

void Passengers::Leaving(string pass) { // This function removes a passenger from the seat
    if (pass == "L") {                  // allocation when they leave the bus
        for (int j = 0; j < 16; j++) {
            if (getArr(j) == "L") {
                setArr(j, "0");
                return;
            }
        }
    }
    else if (pass == "F") {
        for (int j = 0; j < 16; j++) {
            if (getArr(j) == "Mo") {
                setArr(j, "0");                
                break;
            }
        }
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 16; k++) {
                if (getArr(k) == "C") {
                    setArr(k, "0");
                    break;
                }
            }
        }
    }
    else if (pass == "M") {
        for (int j = 16; j < 32; j++) {
            if (getArr(j) == "M") {
                setArr(j, "0");
                return;
            }
        }
    }
    else if (pass == "MT") {
        for (int j = 16; j < 32; j++) {
            if (getArr(j) == "MT") {
                setArr(j, "0");
                return;
            }
        }
    }
}

void Passengers::setPassengers(ifstream& fin, ofstream& fout) {  // this function reads from the passenger data file
    string action, passenger;                                    // and allocate passenger seats for all stops in order
    int passCount = 0, x, stops{ 0 };                            // removing passengers first
    fin >> stops;
    for (int i = 0; i < stops; i++) {
        fin >> action;                                               // also adds stop data to stop data file so seating plan
        while (action != "/") {                                      // for every stop is stored
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
                    else {
                        passenger = action[1];
                    }
                    for (int i = 0; i < passCount; i++) {
                        Leaving(passenger);
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
                    else {
                        passenger = action[1];
                    }
                    for (int i = 0; i < passCount; i++) {
                        Boarding(passenger);
                    }
                    passenger.clear();
                    if (action == "/") {
                        break;
                    }
                }
            }
            fout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 "
                "C = Child), MT = Male Teen\n\n";
            fout << setw(20) << "DOOR\n\n";
            int count = 0, count2 = 0;
            for (int i = 0; i < 32; i++) {
                count++;
                count2++;
                if (getArr(i).size() == 2) {
                    fout << getArr(i) << "  ";
                }
                else {
                    fout << getArr(i) << "   ";
                }
                if (count == 2) {
                    fout << "    ";
                }
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

void Passengers::resetFile(ofstream& fout) {            // this function resets the stop data file when
    fout.open("StopData.txt");                          // the admin calls to reset seating plan
    fout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 C "
        "= Child), MT = Male Teen\n\n";
    fout << setw(20) << "DOOR\n\n";
    int count = 0, count2 = 0;
    for (int i = 0; i < 32; i++) {
        count++;
        count2++;
        if (getArr(i).size() == 2) {
            fout << getArr(i) << "  ";
        }
        else {
            fout << getArr(i) << "   ";
        }
        if (count == 2) {
            fout << "    ";
        }
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

void Passengers::resetData() {
    for (int i = 0; i < 32; i++) {
        setArr(i, "0");
    }
}

void Passengers::DisplayAllocationOrReset(ofstream& fout) {
    int x;
    cout << "Press 'D' for Seat Allocation, Alternatively, Press 'R' to reset seating plan nad Display Default Plan \n\n";
    x = _getch();
    while (x != 100 && x != 114) {                  // This function uses _getch() to read key stroke
        cout << "Please Press 'D' or 'R'\n";        // if D is pressed the if statement is ignored and the seating
        x = _getch();                               // plan is printed
    }                                               // else if R is pressed the seating plan and text file are reset
                                                    // and a default seating plan is printed
    if (x == 114) {
        resetData();
        resetFile(fout);
        cout << "Seating Plan Reset to Default\n\n";
    }

    cout << "Displaying Allocation after Final Stop\n\n";
    cout << "0 = Empty Seat, L = Lady, M = Male, F = Family (1 Mo = Mother, 2 C = Child), MT = Male Teen\n\n";
    int count = 0, count2 = 0;
    cout << setw(20) << "DOOR\n\n";
    for (int i = 0; i < 32; i++) {
        count++;
        count2++;
        if (getArr(i).size() == 2) {
            cout << getArr(i) << "  ";
        }
        else {
            cout << getArr(i) << "   ";
        }
        if (count == 2) {
            cout << "    ";
        }
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
