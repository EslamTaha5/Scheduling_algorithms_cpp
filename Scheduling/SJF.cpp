

#include "Scheduler.h"


// Write your code here to implement the shortest-job first scheduling algorithm
bool cmpSJF(PCB &a, PCB &b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;

}
// compare for priority queue to sort elements base in their burst time
class pq_cmp_SJF {
public:
    bool operator()(const PCB &r, const PCB &l) {
        if (r.burstTime != l.burstTime) return r.burstTime > l.burstTime;
        return r.arrivalTime < l.arrivalTime;
    }
};

void Scheduler::runSJF(vector<PCB> processes) {
    PCB cur_process;
    uint cur_time = 0;
    //Sort based on shortest time and if they are equal sort based on time arrival
    sort(processes.begin(), processes.end(), cmpSJF);
    // add processes to the queue
    int i = 0, n = processes.size();
    // I used priority queue because it will sort all processes automatically based in their burst time
    // when pushing processes that has lower burst time it will become the top of priority queue
    priority_queue<PCB, vector<PCB>, pq_cmp_SJF> pq;
    while (i < n || !pq.empty()) {
        if (pq.empty() && processes[i].arrivalTime < cur_time) {
            cur_time = processes[i].arrivalTime;
        }
        // Here we add processes their arrival time is greater than or equal to current time
        while (i < n && processes[i].arrivalTime <= cur_time) {
            pq.push(processes[i++]);
        }

        //remove first element
        cur_process = pq.top();
        pq.pop();

        // The process will run to completion as one slice
        // creating slice with constructor
        ExecutionSlice ex_slice(cur_process, cur_process.burstTime, cur_time);
        processingHistory.push_back(ex_slice);
        cur_time += cur_process.burstTime;
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
