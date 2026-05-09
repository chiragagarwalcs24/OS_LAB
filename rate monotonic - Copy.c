#include <stdio.h>
#include <math.h>

typedef struct {
    int id, exec, period, remain;
     }
     Task;

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d",&n);
    Task t[n];
    double util=0;
    for(int i=0;i<n;i++){
        printf("Enter execution time and period for Task %d: ",i+1);
        scanf("%d %d",&t[i].exec,&t[i].period);
        t[i].id=i+1;
         t[i].remain=0;
        util += (double)t[i].exec/t[i].period;
    }
    double bound = n*(pow(2.0,1.0/n)-1);
    printf("\nTotal Utilization = %.2f\nRMS Bound = %.2f\n",util,bound);
    if(util<=bound)
        printf("Task set is schedulable under RMS.\n");
    else
    printf("Task set may not be schedulable under RMS.\n");

    int hyper=1;
    for(int i=0;i<n;i++)
        hyper*=t[i].period;
    printf("\n--- Rate Monotonic Scheduling Simulation ---\n");
    for(int time=0; time<hyper; time++){
        for(int i=0;i<n;i++)
        if(time%t[i].period==0)
        t[i].remain=t[i].exec;
        int run=-1;
        for(int i=0;i<n;i++)
        if(t[i].remain>0 && (run==-1||t[i].period<t[run].period)) run=i;
        if(run!=-1){
            printf("Time %2d: Task %d running\n",time,t[run].id);
            t[run].remain--;
    }
        else
            printf("Time %2d: CPU idle\n",time);
    }
}
