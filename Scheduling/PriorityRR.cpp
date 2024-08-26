
#include "Scheduler.h"


// Write your code here to implement the Priority round-robin scheduling algorithm

void Scheduler::runPriorityRR(vector<PCB> processes, uint32_t quanta) {
    sort(processes.begin(), processes.end(), [&](PCB &r, PCB &l) {
        return r.arrivalTime < l.arrivalTime;
    });
    int MAX_P = 0;
    for (auto &it: processes)MAX_P = max(MAX_P, (int) it.priority);
    int n = processes.size();
    PCB cur_process;
    uint cur_time = 0;
    vector<queue<PCB>> vq(MAX_P + 2);
    int i = 0, cnt = n;
    multiset<int> st;
    while (i < n || cnt) {
        if (st.empty() && cur_time < processes[i].arrivalTime)
            cur_time = processes[i].arrivalTime;
        while (i < n && processes[i].arrivalTime <= cur_time) {
            int x = processes[i].priority;
            st.insert(-x);
            vq[x].push(processes[i]);
            i++;
        }
        int x = -*st.begin();
        st.erase(st.begin());
        cur_process = vq[x].front();
        vq[x].pop();
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
            cnt--;
        } else {
            st.insert(-x);
            vq[x].push(cur_process);
        }
    }
}
