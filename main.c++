#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
};

// ---------------- FCFS ----------------
void fcfs(vector<Process> p) {
    int time = 0, n = p.size();
    float wt = 0, tat = 0;

    cout << "\nFCFS Scheduling\n";
    cout << "PID\tWT\tTAT\n";

    for (auto &pr : p) {
        if (time < pr.arrival)
            time = pr.arrival;

        int waiting = time - pr.arrival;
        int turnaround = waiting + pr.burst;

        wt += waiting;
        tat += turnaround;

        time += pr.burst;

        cout << pr.pid << "\t" << waiting << "\t" << turnaround << endl;
    }

    cout << "Average Waiting Time: " << wt / n << endl;
    cout << "Average Turnaround Time: " << tat / n << endl;
}

// ---------------- SJF (Non-Preemptive) ----------------
void sjf(vector<Process> p) {
    int time = 0, completed = 0, n = p.size();
    vector<bool> done(n, false);
    float wt = 0, tat = 0;

    cout << "\nSJF Scheduling\n";
    cout << "PID\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, mn = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < mn) {
                mn = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int waiting = time - p[idx].arrival;
        int turnaround = waiting + p[idx].burst;

        wt += waiting;
        tat += turnaround;

        time += p[idx].burst;
        done[idx] = true;
        completed++;

        cout << p[idx].pid << "\t" << waiting << "\t" << turnaround << endl;
    }

    cout << "Average Waiting Time: " << wt / n << endl;
    cout << "Average Turnaround Time: " << tat / n << endl;
}

// ---------------- SJF (Preemptive) ----------------
void sjfPreemptive(vector<Process> p) {
    int n = p.size();
    vector<int> rem(n);
    vector<int> wt(n, 0), tat(n, 0);
    int completed = 0, time = 0, prev = -1;

    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;

    cout << "\nPreemptive SJF (SRTF)\n";
    cout << "PID\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, mn = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && rem[i] > 0 && rem[i] < mn) {
                mn = rem[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            completed++;
            tat[idx] = time - p[idx].arrival;
            wt[idx] = tat[idx] - p[idx].burst;
        }
    }
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++){
        cout << p[i].pid << "\t" << wt[i] << "\t" << tat[i] << endl;
       totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "Average Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;
}


// ---------------- Priority Scheduling (Non-Preemptive) ----------------
void priorityScheduling(vector<Process> p) {
    int time = 0, completed = 0, n = p.size();
    vector<bool> done(n, false);
    float wt = 0, tat = 0;

    cout << "\nPriority Scheduling\n";
    cout << "PID\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int waiting = time - p[idx].arrival;
        int turnaround = waiting + p[idx].burst;

        wt += waiting;
        tat += turnaround;

        time += p[idx].burst;
        done[idx] = true;
        completed++;

        cout << p[idx].pid << "\t" << waiting << "\t" << turnaround << endl;
    }

    cout << "Average Waiting Time: " << wt / n << endl;
    cout << "Average Turnaround Time: " << tat / n << endl;
}

// ---------------- Priority Scheduling (Preemptive) ----------------
void priorityPreemptive(vector<Process> p) {
    int n = p.size();
    vector<int> rem(n);
    vector<int> wt(n, 0), tat(n, 0);
    int completed = 0, time = 0;

    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;

    cout << "\nPreemptive Priority Scheduling\n";
    cout << "PID\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && rem[i] > 0 && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            completed++;
            tat[idx] = time - p[idx].arrival;
            wt[idx] = tat[idx] - p[idx].burst;
        }
    }
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++){
        cout << p[i].pid << "\t" << wt[i] << "\t" << tat[i] << endl;
        totalWT += wt[i];
        totalTAT += tat[i];
    }

        cout << "Average Waiting Time: " << totalWT / n << endl;
       cout << "Average Turnaround Time: " << totalTAT / n << endl;
}


// ---------------- Round Robin ----------------
void roundRobin(vector<Process> p, int quantum) {
    int time = 0, n = p.size();
    vector<int> rem(n);
    queue<int> q;
    float wt = 0, tat = 0;

    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;

    q.push(0);

    cout << "\nRound Robin Scheduling\n";
    cout << "PID\tWT\tTAT\n";

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (rem[i] > 0) {
            int exec = min(quantum, rem[i]);
            rem[i] -= exec;
            time += exec;

            for (int j = 0; j < n; j++) {
                if (j != i && p[j].arrival <= time && rem[j] > 0)
                    q.push(j);
            }

            if (rem[i] > 0)
                q.push(i);
            else {
                int turnaround = time - p[i].arrival;
                int waiting = turnaround - p[i].burst;
                wt += waiting;
                tat += turnaround;
                cout << p[i].pid << "\t" << waiting << "\t" << turnaround << endl;
            }
        }
    }

    cout << "Average Waiting Time: " << wt / n << endl;
    cout << "Average Turnaround Time: " << tat / n << endl;
}


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << endl;
        p[i].pid = i + 1;
        cout << "Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
        cout << "Priority (lower is higher priority): ";
        cin >> p[i].priority;
    }

    fcfs(p);
    sjf(p);
    sjfPreemptive(p);
    priorityScheduling(p);
    priorityPreemptive(p);

    int quantum;
    cout << "\nEnter Time Quantum for Round Robin: ";
    cin >> quantum;
    roundRobin(p, quantum);

    return 0;
}
