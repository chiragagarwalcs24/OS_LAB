#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
    int remaining;
    bool done;
};

void nonPreemptiveSJF(struct Process p[], int n) {
    int completed = 0, time = 0;
    float avgTAT = 0, avgWT = 0, avgRT = 0;

    while (completed < n) {
        int idx = -1, minBurst = 1e9;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            p[idx].completion = time + p[idx].burst;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].response = time - p[idx].arrival;

            avgTAT += p[idx].turnaround;
            avgWT += p[idx].waiting;
            avgRT += p[idx].response;

            time = p[idx].completion;
            p[idx].done = true;
            completed++;
        }
    }

    printf("\n--- Non-Preemptive SJF ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround,
               p[i].waiting, p[i].response);
    }
    printf("Average TAT: %.2f\nAverage WT: %.2f\nAverage RT: %.2f\n",
           avgTAT/n, avgWT/n, avgRT/n);
}

void preemptiveSJF(struct Process p[], int n) {
    int completed = 0, time = 0;
    float avgTAT = 0, avgWT = 0, avgRT = 0;

    while (completed < n) {
        int idx = -1, minRemaining = 1e9;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].remaining < minRemaining) {
                minRemaining = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            if (p[idx].remaining == p[idx].burst) {
                p[idx].response = time - p[idx].arrival; // first time scheduled
            }
            p[idx].remaining--;
            time++;
            if (p[idx].remaining == 0) {
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;

                avgTAT += p[idx].turnaround;
                avgWT += p[idx].waiting;
                avgRT += p[idx].response;

                p[idx].done = true;
                completed++;
            }
        }
    }

    printf("\n--- Preemptive SJF (SRTF) ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround,
               p[i].waiting, p[i].response);
    }
    printf("Average TAT: %.2f\nAverage WT: %.2f\nAverage RT: %.2f\n",
           avgTAT/n, avgWT/n, avgRT/n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], q[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i+1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].done = false;

        // Copy for preemptive version
        q[i] = p[i];
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            nonPreemptiveSJF(p, n);
            break;
        case 2:
            preemptiveSJF(q, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
