# CSCI 51.01A-Q4
Cabugwang 180806; Enriquez 181832; Villabroza 185216

## Requirements

You will need
* Command Line / Terminal
* Python 3.x to compile and run the Python program (180806-181832-185216-GP1.py)

To run the program, use Python 3.x in your Command Line or Terminal followed by the path to the program (whichever works with your machine's Python installation)
```sh
python 180806-181832-185216-GP1.py
```
or 
```sh
py 180806-181832-185216-GP1.py
```
The Command Line / Terminal will output "Enter number of test cases: " which signifies the start of the program once it successfully compiles. 


## Features

The program simulates different process scheduling algorithms. Given a list of processes and a scheduling algorithm, the program will output a text version of the resulting Gantt chart as well as performance metrics of the scheduling algorithm simulation.

The program uses standard input to accept user input.

The first line of input must be a single integer T denoting the number of test cases.

The next T sets of lines each test case.

The first line of each test case consist of an integer X (X > 0) indicating the number of processes followed by a string S which denotes the type of scheduling algorithm that will be simulated. Algorithms (and string S accounted for) that are featured in the program include:
* FCFS (First Come First Serve)
* SJF (Shortest Job First, Non-preemptive)
* SRTF (Shortest Time Remaining First, SJF Preemptive)
* P (Priority)
* RR (Round Robin) followed by an additional integer Q (Q > 0) on the same line denoting the time quantum or time slice.

The next X lines describes the process which contains three integers, denoting the arrival time, burst time, and priority value of the process respectively.Process indices (PID) are 1-based which means the first process has a PID of 1.

Aside from the Gantt chart, the program will also print our performance metrics for the simulation such as total time elapsed, CPU utilization, total burst time, etc.