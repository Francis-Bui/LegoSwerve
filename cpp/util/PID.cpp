#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <fstream>
using namespace std;
 
// Defining important variables as global to 
// access them from different functions
double kp, ki, kd, midpoint, integral,
lastError, derivative, turn, lightValue, error;

ofstream file, pairsOutput;
ifstream file_;

// generates random number to start the robot on
double getLightValue() {
    return (rand()%100)+1;
}

// Main Menu (for command line tool purposes)
void menu() {
    cout << "Choose the mode: " << "\n";
    cout << "1- Proportional Controller." << "\n";
    cout << "2- Proportional-Integral Controller." << "\n";
    cout << "3- Proportional-Integral-Derivative Controller." << "\n";
    cout << "*************************" << "\n";
}

// Opens the files depending on the choice
// DONT FORGET TO CHANGE THE FILE PATH
void choose(int x) {
    if (x == 1) {
        cout << "Kp = ";
        cin >> kp;
        cout << "Midpoint = "; cin >> midpoint;
        file.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_P.txt");
    } else if (x == 2) {
        cout << "Kp = "; cin >> kp;
        cout << "Ki = "; cin >> ki;
        cout << "Midpoint = "; cin >> midpoint;
        file.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_PI.txt");
    } else if (x == 3) {
        cout << "Kp = "; cin >> kp;
        cout << "Ki = "; cin >> ki;
        cout << "Kd = "; cin >> kd;
        cout << "Midpoint = "; cin >> midpoint;
        file.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_PID.txt");
    } else {
        throw "ERROR";
        return;
    }
}

// Generates the output as pairs to easen the process of graphing 
// the result using a plot grapher
// DONT FORGET TO CHANGE THE FILE PATH
void generatePairs(int x) {
    if (x == 1) {
        file_.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_P.txt");
        pairsOutput.open("/Users/Mohammed/Desktop/PID Simulator/pairsGenerated.txt");
        string s; int y = 2;
        while (getline(file_, s)) {
            if (s[0] == '/') {
                continue;
            }
            pairsOutput << y << ", " << s << "\n";
            y += 2;
        }
    } else if (x == 2) {
        file_.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_PI.txt");
        pairsOutput.open("/Users/Mohammed/Desktop/PID Simulator/pairsGenerated2.txt");
        string s; int y = 2;
        while (getline(file_, s)) {
            if (s[0] == '/') {
                continue;
            }
            pairsOutput << y << ", " << s << "\n";
            y += 2;
        }
    } else if (x == 3) {
        file_.open("/Users/Mohammed/Desktop/PID Simulator/OUTPUT_PID.txt");
        pairsOutput.open("/Users/Mohammed/Desktop/PID Simulator/pairsGenerated3.txt");
        string s; int y = 2;
        while (getline(file_, s)) {
            if (s[0] == '/') {
                continue;
            }
            pairsOutput << y << ", " << s << "\n";
            y += 2;
        }
    } else {
        throw "ERROR"; return;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    menu();
    int x; cin >> x;
    choose(x); 
    
    //kp = 0.7; ki = 0.04; kd = 3;
    //midpoint = 30;
    integral = lastError = derivative = 0;
    
    lightValue = getLightValue();
    //lightValue = 66; //Uncomment this to test on a specific value.
    
    for (;true;) {
        cout << "Light Value = " << lightValue << "\n";
        file << lightValue << "\n";
        
        error = lightValue - midpoint;
        cout << "Error = " << error << "\n";
        
        integral += error;
        cout << "Integral = " << integral << "\n";
        
        derivative = error - lastError;
        cout << "Derivative = " << derivative << "\n";
        
        turn = (kp*error) + (ki*integral) + (kd*derivative);
        cout << "Turn = " << turn << "\n";
        
        if (turn > 0) {
            lightValue -= turn/5;
        } else {
            lightValue += (turn*-1)/5;
        }
        
        lastError = error;
        cout << "Last Error = " << lastError << "\n";
        
        cout << "******************************" << "\n" << "\n";
        
        if (error == 0 || turn > 5000 || turn < -5000) {
            break;
        }
    }
    generatePairs(x);
    return 0;
}