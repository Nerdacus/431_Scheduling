#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure of job
typedef struct {
    int id; // Process ID
    int arrivalTime; // Arrival time
    int cpuBurst; // CPU burst time
    int priority; // Priority
    int compTime; // Completion time 
    int turnTime; // Turnaround time 
    int respTime; // Response time 
    int remBurst; // Remaining burst time (Round Robin)
} Process;

// Compare jobs based on arrival time
int compArrTime(const void *a, const void *b) {
    const Process *job1 = (const Process *)a;
    const Process *job2 = (const Process *)b;
    return job1->arrivalTime - job2->arrivalTime;
}

// First Come, First Serve scheduling algorithm
void fcfs(Process *processes, int numOfProcesses) {
    int currTime = 0;
    float totalTurnTime = 0, totalRespTime = 0;
    printf("\nFirst Come, First Served Scheduling:\n");
    for (int i = 0; i < numOfProcesses; ++i) {
        if (currTime < processes[i].arrivalTime)
            currTime = processes[i].arrivalTime;
        processes[i].respTime = currTime - processes[i].arrivalTime;
        printf("Process %d completed at time %d\n", processes[i].id, currTime + processes[i].cpuBurst);
        processes[i].compTime = currTime + processes[i].cpuBurst;
        currTime += processes[i].cpuBurst;
        processes[i].turnTime = processes[i].compTime - processes[i].arrivalTime;
        totalTurnTime += processes[i].turnTime;
        totalRespTime += processes[i].respTime;
    }
    printf("Average throughput time: %.2f\n", numOfProcesses / (float)currTime);
    printf("Average turnaround time: %.2f\n", totalTurnTime / numOfProcesses);
    printf("Average response time: %.2f\n", totalRespTime / numOfProcesses);
}

// Shortest Job First scheduling algorithm
void sjf(Process *processes, int numOfProcesses) {
    int currTime = 0;
    float totalTurnTime = 0, totalRespTime = 0;
    printf("\nShortest Job First Scheduling:\n");
    
    // Sort processes based on arrival time
    qsort(processes, numOfProcesses, sizeof(Process), compArrTime);
    
    // Array to keep track of completion status of each process
    int *completed = (int *)calloc(numOfProcesses, sizeof(int));

    // Run until all processes are completed
    while (1) {
        int shortestJob = -1; // Index of the shortest job
        int shortestBurst = INT_MAX; // Initialize to a large value

        // Find the shortest job that has arrived and not completed yet
        for (int i = 0; i < numOfProcesses; ++i) {
            if (processes[i].arrivalTime <= currTime && !completed[i]) {
                if (processes[i].cpuBurst < shortestBurst) {
                    shortestBurst = processes[i].cpuBurst;
                    shortestJob = i;
                }
            }
        }

        // If no jobs, break
        if (shortestJob == -1)
            break;

        // Update current time and mark the selected job as completed
        currTime += processes[shortestJob].cpuBurst;
        processes[shortestJob].compTime = currTime;
        processes[shortestJob].turnTime = currTime - processes[shortestJob].arrivalTime;
        processes[shortestJob].respTime = currTime - processes[shortestJob].arrivalTime - processes[shortestJob].cpuBurst;
        totalTurnTime += processes[shortestJob].turnTime;
        totalRespTime += processes[shortestJob].respTime;
        completed[shortestJob] = 1;

        printf("Process %d completed at time %d\n", processes[shortestJob].id, currTime);
    }

    printf("Average throughput time: %.2f\n", numOfProcesses / (float)currTime);
    printf("Average turnaround time: %.2f\n", totalTurnTime / numOfProcesses);
    printf("Average response time: %.2f\n", totalRespTime / numOfProcesses);

    free(completed);
}

// Round Robin scheduling algorithm
void roundRobin(Process *processes, int numOfProcesses, int timeQuantum) {
    int currTime = 0;
    float totalTurnTime = 0, totalRespTime = 0;
    printf("\nRound Robin Scheduling with time quantum %d:\n", timeQuantum);
    int *remBurst = (int *)malloc(numOfProcesses * sizeof(int));
    int *started = (int *)calloc(numOfProcesses, sizeof(int)); // Array to track if a process started execution
    for (int i = 0; i < numOfProcesses; ++i) {
        remBurst[i] = processes[i].cpuBurst;
    }

    while (1) {
        int allCompleted = 1;
        for (int i = 0; i < numOfProcesses; ++i) {
            if (remBurst[i] > 0) {
                allCompleted = 0;
                if (!started[i]) {
                    processes[i].respTime = currTime - processes[i].arrivalTime;
                    started[i] = 1;
                }
                if (remBurst[i] <= timeQuantum) {
                    currTime += remBurst[i];
                    remBurst[i] = 0;
                    printf("Process %d completed at time %d\n", processes[i].id, currTime);
                    processes[i].compTime = currTime;
                    processes[i].turnTime = processes[i].compTime - processes[i].arrivalTime;
                    totalTurnTime += processes[i].turnTime;
                } else {
                    currTime += timeQuantum;
                    remBurst[i] -= timeQuantum;
                }
            }
        }
        if (allCompleted == 1)
            break;
    }
    for (int i = 0; i < numOfProcesses; ++i) {
        totalRespTime += processes[i].respTime;
    }
    printf("Average throughput time: %.2f\n", numOfProcesses / (float)currTime);
    printf("Average turnaround time: %.2f\n", totalTurnTime / numOfProcesses);
    printf("Average response time: %.2f\n", totalRespTime / numOfProcesses);

    free(remBurst);
    free(started);
}

int main() {
    int numOfProcesses, timeQuantum;
    printf("Enter the number of processes: ");
    scanf("%d", &numOfProcesses);
    Process *processes = (Process *)malloc(numOfProcesses * sizeof(Process));
    printf("Enter arrival time, CPU burst, and priority for each process:(# # #)\n");
    for (int i = 0; i < numOfProcesses; ++i) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].cpuBurst, &processes[i].priority);
        processes[i].id = i + 1;
    }

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &timeQuantum);

    // Calling all algorithms
    fcfs(processes, numOfProcesses);
    sjf(processes, numOfProcesses);
    roundRobin(processes, numOfProcesses, timeQuantum);

    free(processes);
    return 0;
}








