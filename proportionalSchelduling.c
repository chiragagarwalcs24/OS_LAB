
#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int share;
};

int main() {

    int n, totalShare = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {

        p[i].id = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burstTime);

        printf("Enter CPU Share (Weight): ");
        scanf("%d", &p[i].share);

        totalShare += p[i].share;
    }

    printf("\n===== Proportional Scheduling =====\n");

    // Calculate proportional CPU allocation
    for (int i = 0; i < n; i++) {

        float cpuPercent;

        cpuPercent =
            ((float)p[i].share / totalShare) * 100;

        printf("\nProcess P%d", p[i].id);

        printf("\nBurst Time = %d", p[i].burstTime);

        printf("\nCPU Share = %d", p[i].share);

        printf("\nCPU Allocation = %.2f%%\n",
               cpuPercent);
    }

    return 0;
}
