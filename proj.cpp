/* CSCI 51.01 Project - Cabugwang, Enriquez, Villabroza */

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
 
/* Defines Process struct */
struct Point3D {
    int arrivalTime;
    int burstTime;
    int priorityValue;
    bool isTerminated = false;
    int waitTime = 0;
    int turnAroundTime = 0;
    int responseTime = 0;
};


/* Main Program */
int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    
    
    cin.clear();
    cin.ignore(1000, '\n'); 

    /* Program Loop */
    for (int i = 0; i < t; i++) {
        /* Initializes and declares n for each test case */
        string s;
        int delimiter_position;
        int processes_count;
        string algorithm;
        cout << "Enter number of processes and the algorithm: ";
        getline(cin,s);

        delimiter_position = s.find(" ");
        processes_count = stoi(s.substr(0, delimiter_position));
        algorithm = s.substr(delimiter_position + 1);


    }
    
    return 0;
}