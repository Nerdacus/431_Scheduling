# Process Scheduling Algorithms

This program implements three process scheduling algorithms in C: First Come, First Serve (FCFS), Shortest Job First (SJF), and Round Robin (RR).

## Description

The program simulates the scheduling of processes using three different algorithms:
1. **First Come, First Serve (FCFS)**: Processes are executed in the order they arrive.
2. **Shortest Job First (SJF)**: Processes with the shortest CPU burst time are executed first.
3. **Round Robin (RR)**: Each process gets a small unit of CPU time (time quantum) to execute. If a process's burst time is greater than the time quantum, it's placed at the end of the queue and the next process is executed.

## Features
- Supports simulation of three process scheduling algorithms.
- User input for the number of processes, arrival time, CPU burst time, and priority.
- Calculation of average throughput time, turnaround time, and response time for each algorithm.

## Usage
1. Compile the program using a C compiler (e.g., GCC): `gcc main.c -o scheduler`.
2. Run the compiled program: `./scheduler`.
3. Follow the on-screen instructions to input the number of processes, arrival time, CPU burst time, priority, and time quantum (for Round Robin).
4. The program will output the scheduling results for each algorithm, including average throughput time, turnaround time, and response time.

## Contributing
Contributions are welcome! If you'd like to contribute to this project, feel free to submit a [pull request](https://github.com/Nerdacus/431_Scheduling/pulls).

## License
This project is licensed under the [MIT License](LICENSE).
