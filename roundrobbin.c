#include <stdio.h>

int main() {
    int n, i, time = 0, remain, tq;
    int at[10], bt[10], rt[10];
    int wt[10], tat[10];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    printf("\nEnter Arrival Time and Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nProcess\tAT\tBT\tTAT\tWT\n");

    int flag;
    while(remain > 0) {
        flag = 0;

        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= time) {

                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                }
                else {
                    time += rt[i];
                    wt[i] = time - at[i] - bt[i];
                    tat[i] = time - at[i];
                    total_wt += wt[i];
                    total_tat += tat[i];
                    rt[i] = 0;
                    remain--;
                }
                flag = 1;
            }
        }


        if(flag == 0) {
            time++;
        }
    }

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
