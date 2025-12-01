//Write a program to compute the finish time, turnaround time and waiting time for FCFS algorithm.


#include <stdio.h>

int main() {
    int n, i;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], ft[n], tat[n], wt[n];

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
    }

    // FCFS Calculations
    ft[0] = bt[0];          // finish time of first process
    tat[0] = ft[0];         // TAT = FT - AT, and AT = 0
    wt[0] = 0;              // waiting time for first process
    
    for (i = 1; i < n; i++) {
        ft[i] = ft[i-1] + bt[i];       // finish time
        tat[i] = ft[i];                // AT = 0
        wt[i] = tat[i] - bt[i];        // waiting time
    }

    // Print the results
    printf("\nProcess\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}

/*
Sample Input:

Enter number of processes: 4
Enter burst time for each process:
P1: 5
P2: 3
P3: 8
P4: 6

Sample Output:

Process	BT	FT	TAT	WT
P1	5	5	5	0
P2	3	8	8	5
P3	8	16	16	8
P4	6	22	22	14

Explanation:
- Arrival times are assumed 0 for all processes (FCFS with no explicit arrival times).
- Finish Time (FT) is cumulative burst times: 5, 5+3=8, 8+8=16, 16+6=22.
- Turnaround Time (TAT) = FT - AT (AT=0), so TAT = FT.
- Waiting Time (WT) = TAT - BT.
*/
