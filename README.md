# CPU Scheduling Algorithms
This project includes a collection of algorithms used for scheduling tasks and processes in various systems.

Agorithms are implemented in C++.

Algorithms included are:

1. First Come First Served (FCFS)
2. Shortest Job First (SJF)
3. Round Robin (RR)
4. Priority
5. Priority with Round Robin

## Algorithms
- [First Come First Served](#First-Come-First-Served)
- [Shortest Job First](#Shortest-Job-First)
- [Round Robin](#Round-Robin)
- [Priority](#Priority)
- [Priority with Round Robin](#Priority-with-Round-Robin)

## First Come First Served :
A simple scheduling method that executes tasks in the order they arrive,
This algorithm can lead to poor performance if there are processes with long burst time. because longer running processes
will block all processes until completing its execution.

## Shortest Job First :
Prioritizes tasks with the shortest execution time.
it can be either preemptive (Shortest Remaining Time First) or non-preemptive. While it can significantly reduce the 
average wait time, it requires knowledge of future task lengths, which can be impractical in real-world scenarios.

## Round Robin :
The Round Robin (RR) scheduling algorithm allocates a fixed time slice or quantum to each task in a
cyclic order. Once a task's time slice expires, it is placed at the end of the queue, and the next task is scheduled.

## Priority :
Priority Scheduling assigns a priority level to each task, and the task with the highest priority is
selected for execution next. This scheduling method can be either preemptive or non-preemptive:
- **Preemptive Priority Scheduling**: A running task may be interrupted if a higher-priority task arrives.
- **Non-Preemptive Priority Scheduling**: The currently running task is not interrupted; instead, new tasks are 
  scheduled based on priority only when the current task completes.

## Priority with Round Robin :
Priority Scheduling with Round Robin combines elements of both Priority Scheduling
and Round Robin. In this method:
- Tasks are first sorted based on priority levels: The highest-priority tasks are considered first.
- Within each priority level, Round Robin scheduling is applied: Tasks are assigned a fixed time slice, and if a
  task's time slice expires, it is moved to the end of the queue for its priority level.

## Input format :
Insert your processes into the file data.txt file in this format:
ProcessName  ArrivalTime  BurstTime  Priority.

all separated by white space.

Then execute main.cpp file and enter the name of the algorithm you want to schedule these tasks with.
