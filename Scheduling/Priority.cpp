

#include "Scheduler.h"

///                            Non-preemptive priority
// Write your code here to implement the priority scheduling algorithm
bool cmpPriority(PCB &a, PCB &b) {
    return a.arrivalTime < b.arrivalTime;

}

class pq_cmp_Priorty {
public:
    bool operator()(const PCB &r, const PCB &l) {
        if (r.priority != l.priority)return r.priority < l.priority;
        return r.arrivalTime > l.arrivalTime;
    }
};

void Scheduler::runPriority(vector<PCB> processes) {
    PCB cur_process;
    uint cur_time = 0;
    priority_queue<PCB, vector<PCB>, pq_cmp_Priorty> pq;
    //Sort based on shortest priority
    sort(processes.begin(), processes.end());
    int i = 0, n = processes.size();
    while (i < n || !pq.empty()) {
        if (pq.empty() && processes[i].arrivalTime < cur_time) {
            cur_time = processes[i].arrivalTime;
        }
        while (i < n && processes[i].arrivalTime <= cur_time) {
            pq.push(processes[i++]);
        }


        cur_process = pq.top();
        pq.pop();

        // The process will run to completion as one slice
        ExecutionSlice ex_slice(cur_process, cur_process.burstTime, cur_time);
        cur_time += cur_process.burstTime;
        processingHistory.push_back(ex_slice);
        totalRunningTime += cur_process.burstTime;
        cur_process.remainingTime = 0;
        if (cur_process.remainingTime == 0) {
            cur_process.endTime = cur_time;
            cur_process.turnAroundTime = cur_process.endTime - cur_process.arrivalTime;
            cur_process.waitingTime = cur_process.endTime - cur_process.arrivalTime - cur_process.burstTime;
            totalWaitingTime += cur_process.waitingTime;
            finishedProcessesCount++;
            terminatedProcesses.push_back(cur_process);
        }
    }
}
