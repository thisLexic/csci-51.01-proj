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

def SRTF(process_list):
    ready_queue = []
    terminated = []

    elapsed_time = 0
    # completed = 0
    total_burst_time = 0

    process_count = len(process_list)

    # process_list = sorted(process_list, key=lambda x: x[2])

    while len(terminated) != process_count:
        for p in process_list:
            if p[1] <= elapsed_time:
                ready_queue.append(p)
                process_list.remove(p)

        ready_queue = sorted(ready_queue, key=lambda x: x[2])   
        if (len(ready_queue) != 0):
            previous_burst_pid = ready_queue[0][0]
         
            # Shortest burst changed in ready queue changed
            if (previous_burst_pid != ready_queue[0][0]):
                print(p[7], " ", p[0], " ", p[2],"X", sep="")

            ready_queue[0][2] -= 1
            elapsed_time += 1

            

            if(ready_queue[0][2]==0):
                terminated.append(ready_queue[0])
                ready_queue.remove(ready_queue[0])

            

        


    print("Total time elapsed: ", elapsed_time, "ns", sep="")
    print("Total CPU burst time: ", total_burst_time, "ns", sep="")
    print("CPU Utilization: ", (total_burst_time/elapsed_time)*100, "%", sep="")
    print("Throughput: ", (process_count/elapsed_time), "processes/ns", sep="")
    get_details(terminated)


def RR(process_list, time_quantum):
    round_robin_queue = []
    terminated = []

    elapsed_time = 0
    total_burst_time = 0

    process_count = len(process_list)

    while len(terminated) != process_count:
        # Adds all viable processes in round robin queue
        for p in process_list:
            if p[1] <= elapsed_time and p[9] == 0:
                p[9] = 1 # Flag Bit
                round_robin_queue.append(p)
                print("Process",p[0], "added to ready queue at", elapsed_time, "entered with the state", p)

        if len(round_robin_queue) != 0:
            for p in round_robin_queue[:]:

                if p[10] == 0:
                    print("Process",p[0], "at", elapsed_time, "entered if with the state", p)
                    p[10] = 1
                    for i in range(time_quantum):
                        p[2] -= 1
                        elapsed_time += 1
                        if p[2] == 0:
                            print("Process",p[0], "terminated at:", elapsed_time)
                            terminated.append(p)
                            round_robin_queue.remove(p)
                            break
                    print("Process",p[0], "at", elapsed_time, "exited if with the state", p)

                else:
                    print("Process",p[0], "at", elapsed_time, "entered else")
                    elements_passed = 0
                    for p in round_robin_queue:
                        elements_passed += p[10]
                    if elements_passed == len(round_robin_queue):
                        print("Process",p[0], "at", elapsed_time, "RESET THE QUEUE")
                        for p in round_robin_queue:
                            print("Process",p[0], "'s p[10] modified at:", elapsed_time)
                            p[10] = 0
                        break


                # print(p[7], " ", p[0], " ", p[2],"", sep="")

                # Check if there are new processes to be added to the round robin queue
                for p in process_list:
                    if p[1] <= elapsed_time and p[9] == 0:
                        p[9] = 1 # Flag Bit
        
                        round_robin_queue.append(p)
                        print("Process",p[0], "added to ready queue at", elapsed_time, "entered with the state", p)
                        
                        print("Process",p[0], "at", elapsed_time, "entered arrival queue with the state", p)
                        p[10] = 1
                        for i in range(time_quantum):
                            p[2] -= 1
                            elapsed_time += 1
                            if p[2] == 0:
                                print("Process",p[0], "terminated at:", elapsed_time)
                                terminated.append(p)
                                round_robin_queue.remove(p)
                                break
 
        else:
            elapsed_time += 1
        
        print("RR queue: ", round_robin_queue, "at", elapsed_time)
        print("Terminated:", terminated, "at", elapsed_time)






if __name__ =="__main__":
    t = int(input("Enter number of test cases: "))

    for i in range(t):
        processes = []
        s = input("Enter number of processes and the algorithm: ").split()

        for j in range(int(s[0])):
            # Process ID [0], Arrival Time [1], Burst Time [2], Priority [3], Wait Time [4], 
            # Turnaround Time [5], Response Time [6], Start Time [7], Finish Time [8], Flag Bit [9], Terminated [10]
            processes.append([j+1]+list(map(int, input().split()))
+[0,0,0,0,0,0,0])
        
        print(str(i+1), ". ", s[1], sep="")

        if (s[1] == "FCFS"):
            FCFS(processes)

        elif(s[1] == "SJF"):
            SJF(processes)

        elif(s[1] == "SRTF"):
            SRTF(processes)

        # elif(s[1] == "P"):
        #     PRIO(processes)
        
        elif(s[1] == "RR"):
            RR(processes, int(s[2]))
 