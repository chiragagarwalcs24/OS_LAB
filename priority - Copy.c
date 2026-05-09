#include <stdio.h>

int main() {
    int n, i, j;
    int at[10], bt[10], pr[10];
    int ct[10], wt[10], tat[10];
    int temp;

    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time, Burst Time and Priority:\n");
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);

        printf("P%d Priority: ", i+1);
        scanf("%d", &pr[i]);
    }


    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(pr[i] > pr[j]) {

                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;


                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }


    ct[0] = at[0] + bt[0];
    for(i = 1; i < n; i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }


    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
