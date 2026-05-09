#include <stdio.h>

typedef struct {
    int id;
    int weight;
    int share;
} Task;

int main() {
    int n, i, j, totalWeight = 0, totalTime;
    Task t[10];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Enter Weight: ");
        scanf("%d", &t[i].weight);

        totalWeight += t[i].weight;
    }

    printf("\nEnter total CPU time: ");
    scanf("%d", &totalTime);


    for(i = 0; i < n; i++) {
        t[i].share = (t[i].weight * totalTime) / totalWeight;
    }

    printf("\nProportional Scheduling:\n");

    int currentTime = 0;

    for(i = 0; i < n; i++) {

        for(j = 0; j < t[i].share; j++) {

            printf("Time %d -> Task %d Executing\n",
                   currentTime,
                   t[i].id);

            currentTime++;
        }
    }

    return 0;
}
