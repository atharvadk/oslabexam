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

/*
Sample Input:

Enter number of processes: 4
Enter burst time for each process:
P1: 5
P2: 3
P3: 1
P4: 2
Enter Time Quantum: 2

Sample Output:

Process	BT	FT	TAT	WT
P1	5	11	11	6
P2	3	10	10	7
P3	1	5	5	4
P4	2	7	7	5

Gantt (time slices example):
P1(0-2) P2(2-4) P3(4-5) P4(5-7) P1(7-9) P2(9-10) P1(10-11)

Explanation:
- Arrival times are assumed 0 for all processes.
- Time quantum is 2. The scheduler cycles through ready processes giving each up to 2 units.
- Finish times (FT) are recorded when remaining time reaches 0; TAT = FT - AT (AT=0), WT = TAT - BT.
*/
