//Write a program to compute the finish time, turnaround time and waiting time for SJF algorithm.


#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], p[n], ft[n], tat[n], wt[n];
    int i, j;

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // store process ID
    }

    // Sort processes by burst time (Ascending)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // First process calculations
    ft[0] = bt[0];
    tat[0] = ft[0];
    wt[0] = 0;

    // Remaining processes
    for (i = 1; i < n; i++) {
        ft[i] = ft[i - 1] + bt[i];
        tat[i] = ft[i];
        wt[i] = tat[i] - bt[i];
    }

    // Print results
    printf("\nProcess\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
