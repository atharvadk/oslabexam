//Write a program to compute the finish time, turnaround time and waiting time for preemptive priority scheduling algorithm.

#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n], ft[n], tat[n], wt[n];
    int completed = 0, time = 0, smallest, i;
    int high = 999999;  // large priority value

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess P%d:\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower = higher priority): ");
        scanf("%d", &pr[i]);
        rt[i] = bt[i];  // remaining time initialized
    }

    // Preemptive scheduling
    while (completed != n) {
        smallest = -1;

        // find process with highest priority among available ones
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (smallest == -1 || pr[i] < pr[smallest]) {
                    smallest = i;
                }
            }
        }

        if (smallest == -1) {
            time++; // CPU idle
            continue;
        }

        // Execute 1 unit of the selected process
        rt[smallest]--;
        time++;

        // If process finished
        if (rt[smallest] == 0) {
            completed++;
            ft[smallest] = time;  // finish time
        }
    }

    // Calculate TAT and WT
    for (i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Print result
    printf("\nProcess\tAT\tBT\tPR\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
