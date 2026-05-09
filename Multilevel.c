#include <stdio.h>

struct process
{
    int pid;
    int burst;
    int waiting;
    int turnaround;
};

int main()
{
    int i, n1, n2;
    int time = 0;
    float avg_wt = 0, avg_tat = 0;

    struct process sys[10], user[10];

    printf("Enter number of System Processes: ");
    scanf("%d", &n1);

    for(i = 0; i < n1; i++)
    {
        printf("Enter Burst Time for System Process %d: ", i+1);
        scanf("%d", &sys[i].burst);
        sys[i].pid = i + 1;
    }

    printf("\nEnter number of User Processes: ");
    scanf("%d", &n2);

    for(i = 0; i < n2; i++)
    {
        printf("Enter Burst Time for User Process %d: ", i+1);
        scanf("%d", &user[i].burst);
        user[i].pid = i + 1;
    }

    printf("\nSystem Process Execution (Higher Priority - FCFS)\n");
    printf("PID\tBT\tWT\tTAT\n");

    for(i = 0; i < n1; i++)
    {
        sys[i].waiting = time;
        sys[i].turnaround = sys[i].waiting + sys[i].burst;

        time += sys[i].burst;

        avg_wt += sys[i].waiting;
        avg_tat += sys[i].turnaround;

        printf("S%d\t%d\t%d\t%d\n", sys[i].pid, sys[i].burst, sys[i].waiting, sys[i].turnaround);
    }

    printf("\nUser Process Execution (Lower Priority - FCFS)\n");
    printf("PID\tBT\tWT\tTAT\n");

    for(i = 0; i < n2; i++)
    {
        user[i].waiting = time;
        user[i].turnaround = user[i].waiting + user[i].burst;

        time += user[i].burst;

        avg_wt += user[i].waiting;
        avg_tat += user[i].turnaround;

        printf("U%d\t%d\t%d\t%d\n", user[i].pid, user[i].burst, user[i].waiting, user[i].turnaround);
    }

    avg_wt = avg_wt / (n1 + n2);
    avg_tat = avg_tat / (n1 + n2);

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
