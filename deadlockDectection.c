
#include <stdio.h>

int main() {

    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m], finish[n];

    printf("\nEnter Allocation Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {

        int flag = 0;

        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                flag = 1;
                break;
            }
        }

        if(flag)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    int changed = 1;

    while(changed) {

        changed = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(j = 0; j < m; j++) {

                    if(request[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    int deadlock = 0;

    printf("\nProcesses in Deadlock:\n");

    for(i = 0; i < n; i++) {

        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("No Deadlock Detected");
    }

    printf("\n");

    return 0;
}
