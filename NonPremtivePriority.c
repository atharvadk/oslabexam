//Write a program to compute the finish time, turnaround time and waiting time for Non-preemptive priority scheduling algorithm.

#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n], bt[n], pr[n], ft[n], tat[n], wt[n];
    int i, j;

    // Input burst time and priority
    printf("Enter Burst Time and Priority (lower value = higher priority):\n");
    for (i = 0; i < n; i++) {
        printf("P%d BT: ", i+1);
        scanf("%d", &bt[i]);
        printf("P%d Priority: ", i+1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;  // store process ID
    }

    // Sort by priority (ascending)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pr[j] > pr[j + 1]) {
                // swap priority
                int temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                // swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // swap process ID
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // First process computations
    ft[0] = bt[0];
    tat[0] = ft[0];
    wt[0] = 0;

    // Remaining processes
    for (i = 1; i < n; i++) {
        ft[i] = ft[i - 1] + bt[i];
        tat[i] = ft[i];
        wt[i] = tat[i] - bt[i];
    }

    // Output
    printf("\nProcess\tPriority\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\n", p[i], pr[i], bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
