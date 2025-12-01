#include <stdio.h>

int main() {
    int n, m;  // n = number of processes, m = number of resource types
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation matrix (row-wise):\n");
    for (i = 0; i < n; i++) {
        printf("Allocation for P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max matrix (row-wise):\n");
    for (i = 0; i < n; i++) {
        printf("Max for P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix = Max - Allocation
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Display Need Matrix (optional)
    printf("\nNeed matrix:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[n];
    for (i = 0; i < n; i++) {
        finish[i] = 0; // none finished initially
    }

    int safeSeq[n];
    int count = 0; // number of processes in safe sequence

    // Safety Algorithm
    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) { // process not yet finished
                int canAllocate = 1;

                // Check if need[i] <= avail
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    // Pretend to allocate: process i can finish
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j]; // release resources
                    }

                    safeSeq[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            // No process could be allocated in this pass → unsafe
            break;
        }
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
        for (i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state (no safe sequence exists).\n");
    }

    return 0;
}

/*
Sample Input:

Enter number of processes: 5
Enter number of resource types: 3

Enter Allocation matrix (row-wise):
Allocation for P0: 0 1 0
Allocation for P1: 2 0 0
Allocation for P2: 3 0 2
Allocation for P3: 2 1 1
Allocation for P4: 0 0 2

Enter Max matrix (row-wise):
Max for P0: 7 5 3
Max for P1: 3 2 2
Max for P2: 9 0 2
Max for P3: 2 2 2
Max for P4: 4 3 3

Enter Available resources: 3 3 2

Sample Output:

Need matrix:
P0: 7 4 3 
P1: 1 2 2 
P2: 6 0 0 
P3: 0 1 1 
P4: 4 3 1 

System is in a SAFE state.
Safe sequence is: P1 -> P3 -> P4 -> P0 -> P2

Explanation:
- The Need matrix is computed as Max - Allocation for each process and resource.
- The safety algorithm finds a sequence of processes that can finish with available resources.
- For the example, one safe sequence is P1, P3, P4, P0, P2.
*/
