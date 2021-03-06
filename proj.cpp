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

    bool operator < (const Process& str) const
    {
        return (id < str.id);
    }
};

// get the Process with the smallest arrival time
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

// get the Id of the Process with the smallest arrival time
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

// get the Process with the smallest arrival time and in the case of ties, smallest burst time
Process getSmallestArrivalTimeBurst(vector<Process> process_list, int processes_count, int elapsed){
    Process shortest = process_list[0];
    Process tryShortest;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.arrivalTime <= elapsed && tryShortest.burstTime < shortest.burstTime ) {
            shortest = tryShortest;
        }
    }
    
    return shortest;
};

// get the id of the Process with the smallest arrival time and in the case of ties, smallest burst time
int getSmallestArrivalTimeIdBurst(vector<Process> process_list, int processes_count, int elapsed){
    Process shortest = process_list[0];
    Process tryShortest;
    int value = 0;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.arrivalTime <= elapsed && tryShortest.burstTime < shortest.burstTime ) {
            shortest = tryShortest;
            value = i;
        }
    }
    
    return value;
};
 
// get the Process with the smallest arrival time and in the case of ties, smallest burst time
Process getSmallestBurstTime(vector<Process> process_list, int processes_count, int elapsed){
    Process shortest = process_list[0];
    Process tryShortest;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.burstTime < shortest.burstTime ) {
            shortest = tryShortest;
        }
    }
    
    return shortest;
};

// get the id of the Process with the smallest arrival time and in the case of ties, smallest burst time
int getSmallestBurstTimeId(vector<Process> process_list, int processes_count, int elapsed){
    Process shortest = process_list[0];
    Process tryShortest;
    int value = 0;
    
    for( int i = 1; i < processes_count; i = i + 1 ) {
        tryShortest = process_list[i];
        if ( tryShortest.burstTime < shortest.burstTime ) {
            shortest = tryShortest;
            value = i;
        }
    }
    
    return value;
};

// use for printing out the waiting time, turnaround time, and response time
void getDetails(vector<Process> process_list, int processes_count){
    sort(process_list.begin(), process_list.end());
    Process p;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;

    cout << "Waiting Times:" << "\n";
    for( int i = 0; i < processes_count; i = i + 1 ) {
        p = process_list[i];
        cout << "Process " << p.id << ": " << p.waitTime << "ns\n";
        totalWaitingTime = totalWaitingTime + p.waitTime;
    }
    cout << "Average waiting time: " << static_cast<float>(totalWaitingTime)/static_cast<float>(processes_count) << "ns\n";

    cout << "Turnaround times:" << "\n";
    for( int i = 0; i < processes_count; i = i + 1 ) {
        p = process_list[i];
        cout << "Process " << p.id << ": " << p.turnAroundTime << "ns\n";
        totalTurnAroundTime = totalTurnAroundTime + p.turnAroundTime;
    }
    cout << "Average turnaround time: " << static_cast<float>(totalTurnAroundTime)/static_cast<float>(processes_count) << "ns\n";

    cout << "Response times:" << "\n";
    for( int i = 0; i < processes_count; i = i + 1 ) {
        p = process_list[i];
        cout << "Process " << p.id << ": " << p.responseTime << "ns\n";
        totalResponseTime = totalResponseTime + p.responseTime;
    }
    cout << "Average response time: " << static_cast<float>(totalResponseTime)/static_cast<float>(processes_count) << "ns\n";
    
}

// prints out the running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
// it returns the vector with the right values for waiting time, turnaround time, and response time
vector<Process> fcfs(vector<Process> process_list, int processes_count){
    vector<Process> return_process_list;
    Process p;
    int pi;
    int elapsedTime = 0;
    int totalBurstTime = 0;
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

        if ( p.arrivalTime < elapsedTime ) {
            p.waitTime = elapsedTime - p.arrivalTime;
        }
        else {
            p.waitTime = 0;
        }

        p.turnAroundTime = p.waitTime + p.burstTime;
        p.responseTime = p.waitTime;

        cout << startTime << " " << p.id << " " << p.burstTime << "X\n";
        elapsedTime = p.burstTime + startTime;
        totalBurstTime = totalBurstTime + p.burstTime;
        process_list.erase(process_list.begin() + pi);

        return_process_list.push_back(p);
    }

    cout << "Total time elapsed:  " << elapsedTime << "ns" << "\n";
    cout << "Total CPU burst time:  " << totalBurstTime << "ns" << "\n";
    cout << "CPU Utilization:  " << (static_cast<float>(totalBurstTime)/static_cast<float>(elapsedTime))*100 << "%" << "\n";
    cout << "Throughput:  " << static_cast<float>(processes_count)/static_cast<float>(elapsedTime) << " processes/ns" << "\n";

    return return_process_list;
};

// prints out the running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
// it returns the vector with the right values for waiting time, turnaround time, and response time
vector<Process> sjf(vector<Process> process_list, int processes_count){
    vector<Process> return_process_list;
    Process p;
    int pi;
    int elapsedTime = 0;
    int totalBurstTime = 0;
    int startTime = 0;
    int completed = 0;
    for( int i = 0; i < processes_count; i = i + 1 ) {
        p = getSmallestArrivalTimeBurst(process_list, processes_count - i, elapsedTime);
        pi = getSmallestArrivalTimeIdBurst(process_list, processes_count - i, elapsedTime);
        if (p.arrivalTime > elapsedTime){
            startTime = p.arrivalTime;
        }
        else {
            startTime = elapsedTime;
        }

        if ( p.arrivalTime < elapsedTime ) {
            p.waitTime = elapsedTime - p.arrivalTime;
        }
        else {
            p.waitTime = 0;
        }

        p.turnAroundTime = p.waitTime + p.burstTime;
        p.responseTime = p.waitTime;

        cout << startTime << " " << p.id << " " << p.burstTime << "X\n";
        elapsedTime = p.burstTime + startTime;
        totalBurstTime = totalBurstTime + p.burstTime;
        process_list.erase(process_list.begin() + pi);

        return_process_list.push_back(p);
    }

    cout << "Total time elapsed:  " << elapsedTime << "ns" << "\n";
    cout << "Total CPU burst time:  " << totalBurstTime << "ns" << "\n";
    cout << "CPU Utilization:  " << (static_cast<float>(totalBurstTime)/static_cast<float>(elapsedTime))*100 << "%" << "\n";
    cout << "Throughput:  " << static_cast<float>(processes_count)/static_cast<float>(elapsedTime) << " processes/ns" << "\n";

    return return_process_list;
};

vector<Process> srtf(vector<Process> process_list, int processes_count){
    vector<Process> return_process_list;
    struct Process p;
    struct Process *ptr_p;
    int pi;
    int elapsedTime = 0;
    int totalBurstTime = 0;
    int startTime = 0;
    int completed = 0;

    while (completed != processes_count){
        for( int i = 0; i < processes_count; i = i + 1 ) {
            p = getSmallestArrivalTimeBurst(process_list, processes_count - i, elapsedTime);
            pi = getSmallestArrivalTimeIdBurst(process_list, processes_count - i, elapsedTime);
            ptr_p = &p;
        }

        // p.arrivalTime = elapsedTime;

        ++(ptr_p -> burstTime);

        elapsedTime++;
        totalBurstTime++;

        cout << elapsedTime << " " << p.id << " " << p.burstTime << "X\n";

        if(p.burstTime == 0){
            completed++;
            process_list.erase(process_list.begin() + pi);
            return_process_list.push_back(p);
        }
    }

    cout << "Total time elapsed:  " << elapsedTime << "ns" << "\n";
    cout << "Total CPU burst time:  " << totalBurstTime << "ns" << "\n";
    cout << "CPU Utilization:  " << (static_cast<float>(totalBurstTime)/static_cast<float>(elapsedTime))*100 << "%" << "\n";
    cout << "Throughput:  " << static_cast<float>(processes_count)/static_cast<float>(elapsedTime) << " processes/ns" << "\n";

    return return_process_list;
};



/* Main Program */
int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    
    

    /* Program Loop */
    for (int i = 0; i < t; i++) {
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
            vector<Process> return_process_list;
            // prints out running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
            return_process_list = fcfs(process_list, processes_count);
            // use for printing out the waiting time, turnaround time, and response time
            getDetails(return_process_list, processes_count);
        }

        else if (algorithm == "SJF"){
            vector<Process> return_process_list;
            // prints out running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
            return_process_list = sjf(process_list, processes_count);
            // use for printing out the waiting time, turnaround time, and response time
            getDetails(return_process_list, processes_count);
        } 

        else if (algorithm == "SRTF"){
            vector<Process> return_process_list;
            // prints out running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
            return_process_list = srtf(process_list, processes_count);
            // use for printing out the waiting time, turnaround time, and response time
            getDetails(return_process_list, processes_count);
        } 

        else if (algorithm == "P"){
            vector<Process> return_process_list;
            // prints out running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
            // return_process_list = prio(process_list, processes_count);
            // use for printing out the waiting time, turnaround time, and response time
            getDetails(return_process_list, processes_count);
        } 
    
        else if (algorithm == "RR"){
            vector<Process> return_process_list;
            // prints out running statistics as well as the total time elapsed, total CPU burst, cpu utilization, and throughput
            // return_process_list = rr(process_list, processes_count);
            // use for printing out the waiting time, turnaround time, and response time
            getDetails(return_process_list, processes_count);
        } 

    }
    
    return 0;
}