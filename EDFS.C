#include <stdio.h>

typedef struct {
    int id, exec, period, remain, deadline;

 } Task;

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d",&n);
    Task t[n];
     int ok=1;

    for(int i=0;i<n;i++){
        printf("Enter execution time and deadline for Task %d: ",i+1);
        scanf("%d %d",&t[i].exec,&t[i].period);
        t[i].id=i+1;
        t[i].remain=0;
        t[i].deadline=t[i].period;
        if((double)t[i].exec/t[i].period>1.0) ok=0;
    }

    printf("\n--- EDF Schedulability Check ---\n");
    printf(ok? "All tasks satisfy Ci/Di <= 1\n":"One or more tasks violate Ci/Di <= 1\n");

    int hyper=1;
    for(int i=0;i<n;i++)
        hyper*=t[i].period;
    printf("\n--- Earliest Deadline First Simulation ---\n");
    for(int time=0; time<hyper; time++){
        for(int i=0;i<n;i++)
            if(time%t[i].period==0){
                 t[i].remain=t[i].exec;
    t[i].deadline=time+t[i].period;
        }
        int run=-1;
        for(int i=0;i<n;i++)
            if(t[i].remain>0 && (run==-1||t[i].deadline<t[run].deadline)) run=i;
        if(run!=-1){
                printf("Time %2d: Task %d running\n",time,t[run].id);
        t[run].remain--;
        }
        else
            printf("Time %2d: CPU idle\n",time);
    }
}
