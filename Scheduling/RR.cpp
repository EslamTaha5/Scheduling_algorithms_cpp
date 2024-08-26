


#include "Scheduler.h"


// Write your code here to implement the round-robin scheduling algorithm


void Scheduler::runRR(vector<PCB> processes, uint32_t quanta) {
    PCB cur_process;
    queue<PCB> q;
    sort(processes.begin(), processes.end());
    uint cur_time = 0;
    int i = 0, n = processes.size();
    while (i < n || !q.empty()) {
        if (q.empty() && processes[i].arrivalTime < cur_time) {
            cur_time = processes[i].arrivalTime;
        }
        //  add processes that have arrived untill now
        while (i < n && processes[i].arrivalTime <= cur_time) {
            q.push(processes[i++]);
        }
        cur_process = q.front();
        q.pop();
        int mn = min(quanta, cur_process.remainingTime);
        ExecutionSlice ex_slice(cur_process, mn, cur_time);
        cur_time += mn;
        processingHistory.push_back(ex_slice);
        totalRunningTime += mn;
        cur_process.remainingTime -= mn;
        if (cur_process.remainingTime == 0) {
            cur_process.endTime = cur_time;
            cur_process.turnAroundTime = cur_time - cur_process.arrivalTime;
            cur_process.waitingTime = cur_time - cur_process.arrivalTime - cur_process.burstTime;

            totalWaitingTime += cur_process.waitingTime;
            finishedProcessesCount++;
            terminatedProcesses.push_back(cur_process);
        } else q.push(cur_process);

    }
}

