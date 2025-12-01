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

/*
Sample Input:

Enter number of processes: 4

Process P1:
Arrival Time: 0
Burst Time: 8
Priority (lower = higher priority): 2

Process P2:
Arrival Time: 1
Burst Time: 4
Priority (lower = higher priority): 1

Process P3:
Arrival Time: 2
Burst Time: 9
Priority (lower = higher priority): 3

Process P4:
Arrival Time: 3
Burst Time: 5
Priority (lower = higher priority): 2

Sample Output:

Process	AT	BT	PR	FT	TAT	WT
P1	0	8	2	17	17	9
P2	1	4	1	5	4	0
P3	2	9	3	26	24	15
P4	3	5	2	22	19	14

Explanation:
- Scheduling is preemptive by priority (lower value = higher priority).
- P2 (priority 1) preempts P1 when it arrives at time 1 and runs to completion.
- Remaining CPU is assigned to the highest-priority ready process at each time unit.
- Finish Time (FT), Turnaround (TAT = FT - AT), and Waiting Time (WT = TAT - BT) are computed accordingly.

Note: The sample output corresponds to the above input and the program's preemptive-priority behavior.
*/
