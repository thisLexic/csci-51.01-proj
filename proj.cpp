/* CSCI 51.01 Project - Cabugwang, Enriquez, Villabroza */

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>

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

Process getSmallestArrivalTime(vector<Process> process_list, int processes_count){
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

int getSmallestArrivalTimeId(vector<Process> process_list, int processes_count){
    Process shortest = process_list[0];
    Process tryShortest;
    int value = 0;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.arrivalTime < shortest.arrivalTime ) {
            shortest = tryShortest;
            value = i;
        }
    }
    
    return value;
};

int fcfs(vector<Process> process_list, int processes_count){
    Process p;
    int pi;
    int elapsedTime = 0;
    int startTime;
    for( int i = 0; i < processes_count; i = i + 1 ) {
        p = getSmallestArrivalTime(process_list, processes_count - i);
        pi = getSmallestArrivalTimeId(process_list, processes_count - i);
        if (p.arrivalTime > elapsedTime){
            startTime = p.arrivalTime;
        }
        else {
            startTime = elapsedTime;
        }

        cout << startTime << " " << p.id << " " << p.burstTime << "X\n";
        elapsedTime = p.burstTime + startTime;
        process_list.erase(process_list.begin() + pi);


    }

    return elapsedTime;
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


        vector<Process> process_list;
        
        for (int j = 1; j <= processes_count; j++) {
            Process process;

            cin>>process.arrivalTime;
            cin>>process.burstTime;
            cin>>process.priorityValue;
            process.id = j;

            process_list.push_back(process);
        }

        cout << i + 1 << ". " << algorithm << "\n";

        if (algorithm == "FCFS") {
            cout << fcfs(process_list, processes_count) << "\n";
            
        }


    }
    
    return 0;
}