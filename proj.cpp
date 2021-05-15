/* CSCI 51.01 Project - Cabugwang, Enriquez, Villabroza */

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
 
/* Defines Process struct */
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priorityValue;
    bool isTerminated = false;
    int waitTime = 0;
    int turnAroundTime = 0;
    int responseTime = 0;
};

Process getSmallestArrivalTime(Process process_list[], int processes_count){
    Process shortest = process_list[0];
    Process tryShortest;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.arrivalTime < shortest.arrivalTime ) {
            shortest = tryShortest;
        }
    }
    
    return shortest;
};

int fcfs(Process process_list[], int processes_count){
    return getSmallestArrivalTime(process_list, processes_count).arrivalTime;
};

/* Main Program */
int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    
    

    /* Program Loop */
    for (int i = 0; i < t; i++) {
        /* Initializes and declares n for each test case */
        cin.clear();
        cin.ignore(1000, '\n'); 
        string s;
        int delimiter_position;
        int processes_count;
        string algorithm;
        cout << "Enter number of processes and the algorithm: ";
        getline(cin,s);

        delimiter_position = s.find(" ");
        processes_count = stoi(s.substr(0, delimiter_position));
        algorithm = s.substr(delimiter_position + 1);


        Process process_list[processes_count];
        
        for (int j = 1; j <= processes_count; j++) {
            Process process;

            cin>>process.arrivalTime;
            cin>>process.burstTime;
            cin>>process.priorityValue;
            process.id = j;

            process_list[j-1] = process;
        }

        cout << i + 1 << ". " << algorithm << "\n";

        if (algorithm == "FCFS") {
            cout << fcfs(process_list, processes_count) << "\n";
            
        }


    }
    
    return 0;
}