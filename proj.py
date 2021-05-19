def get_details(process_list):
    process_list.sort()
    process_count = len(process_list)

    total_waiting_time = 0
    total_turnaround_time = 0
    total_response_time = 0

    print("Waiting times: ")
    for p in process_list:
        print(" Process ", p[0], ": ", p[4], "ns", sep="")
        total_waiting_time += p[4]
    print("Average waiting time: ", total_waiting_time/process_count, "ns", sep="")

    print("Turnaround times: ")
    for p in process_list:
        print(" Process ", p[0], ": ", p[5], "ns", sep="")
        total_turnaround_time += p[5]
    print("Average turnaround time: ", total_turnaround_time/process_count, "ns", sep="")

    print("Response times: ")
    for p in process_list:
        print(" Process ", p[0], ": ", p[6], "ns", sep="")
        total_response_time += p[6]
    print("Average response time: ", total_response_time/process_count, "ns", sep="")


def FCFS(process_list):
    ready_queue = []
    terminated = []

    elapsed_time = 0
    completed = 0
    total_burst_time = 0

    process_count = len(process_list)

    while completed != process_count:

        # Checks if there are processes we can add to the ready queue
        for process in process_list:
            # If there are processes available to be added
            # to the ready queue, then this moves 
            # the process to the ready queue
            if process[1] <= elapsed_time:
                ready_queue.append(process)
                process_list.remove(process)

        if (len(ready_queue)!= 0):        
            while (len(ready_queue)!= 0):
                for p in ready_queue:
                    if p[1] > elapsed_time:
                        p[7] = p[1]
                    else:
                        p[7] = elapsed_time

                    if p[1] < elapsed_time:
                        p[4] = elapsed_time - p[1] 
                    p[5] = p[4] + p[2]
                    p[6] = p[4]

                    elapsed_time += p[2]
                    total_burst_time += p[2]

                    print(p[7], " ", p[0], " ", p[2],"X", sep="")

                    terminated.append(p)
                    ready_queue.remove(p)

                    completed += 1
        else:
            elapsed_time += 1 

    print("Total time elapsed: ", elapsed_time, "ns", sep="")
    print("Total CPU burst time: ", total_burst_time, "ns", sep="")
    print("CPU Utilization: ", (total_burst_time/elapsed_time)*100, "%", sep="")
    print("Throughput: ", (process_count/elapsed_time), "processes/ns", sep="")
    get_details(terminated)

def SJF(process_list):
    ready_queue = []
    terminated = []

    elapsed_time = 0
    completed = 0
    total_burst_time = 0

    process_count = len(process_list)

    process_list = sorted(process_list, key=lambda x: x[2])


    while completed != process_count:

        # Checks if there are processes we can add to the ready queue
        for process in process_list:
            # If there are processes available to be added
            # to the ready queue, then this moves 
            # the process to the ready queue
            if process[1] <= elapsed_time:
                ready_queue.append(process)
                process_list.remove(process)
                break

        if (len(ready_queue)!= 0):        
            while (len(ready_queue)!= 0):
                for p in ready_queue:
                    if p[1] > elapsed_time:
                        p[7] = p[1]
                    else:
                        p[7] = elapsed_time

                    if p[1] < elapsed_time:
                        p[4] = elapsed_time - p[1] 
                    p[5] = p[4] + p[2]
                    p[6] = p[4]

                    elapsed_time += p[2]
                    total_burst_time += p[2]

                    print(p[7], " ", p[0], " ", p[2],"X", sep="")

                    terminated.append(p)
                    ready_queue.remove(p)

                    completed += 1
        else:
            elapsed_time += 1 

    print("Total time elapsed: ", elapsed_time, "ns", sep="")
    print("Total CPU burst time: ", total_burst_time, "ns", sep="")
    print("CPU Utilization: ", (total_burst_time/elapsed_time)*100, "%", sep="")
    print("Throughput: ", (process_count/elapsed_time), "processes/ns", sep="")
    get_details(terminated)


if __name__ =="__main__":
    t = int(input("Enter number of test cases: "))

    for i in range(t):
        processes = []
        s = input("Enter number of processes and the algorithm: ").split()

        for j in range(int(s[0])):
            # Process ID [0], Arrival Time [1], Burst Time [2], Priority [3], 
            # Wait Time [4], Turnaround Time [5], Response Time [6], Start Time [7]
            processes.append([j+1]+list(map(int, input().split()))
+[0,0,0,0])
        
        print(str(i+1), ". ", s[1], sep="")

        if (s[1]=="FCFS"):
            FCFS(processes)

        elif(s[1] == "SJF"):
            SJF(processes)


 