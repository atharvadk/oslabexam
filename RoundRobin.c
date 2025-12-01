//Write a program to compute the finish time, turnaround time and waiting time for Round Robin algorithm.


#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], ft[n], tat[n], wt[n];
    int i;

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // remaining time initially = burst time
    }

    // Time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0;   // Current time
    int done;

    while (1) {
        done = 1;

        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0; // At least one process left

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ft[i] = time; // finish time
                }
            }
        }

        if (done == 1)
            break;
    }

    // Calculate TAT and WT
    for (i = 0; i < n; i++) {
        tat[i] = ft[i];          // AT = 0, so TAT = FT
        wt[i] = tat[i] - bt[i];  // WT = TAT - BT
    }

    // Display results
    printf("\nProcess\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
