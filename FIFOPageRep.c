//Write a program to calculate the number of page faults for a reference string for FIFO page replacement algorithm.

#include <stdio.h>

int main() {
    int n_frames, n_refs;
    int i, j, k, page, faults = 0, pointer = 0;

    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n_refs);

    int ref[n_refs];
    int frames[n_frames];

    // Input reference string
    printf("Enter the reference string (space-separated page numbers):\n");
    for (i = 0; i < n_refs; i++) {
        scanf("%d", &ref[i]);
    }

    // Initialize frames to -1 (empty)
    for (i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    // FIFO Page Replacement
    for (i = 0; i < n_refs; i++) {
        page = ref[i];
        int hit = 0;

        // Check if page is already in any frame (HIT?)
        for (j = 0; j < n_frames; j++) {
            if (frames[j] == page) {
                hit = 1;
                break;
            }
        }

        // If MISS (page fault), replace using FIFO
        if (!hit) {
            frames[pointer] = page;                 // replace oldest page
            pointer = (pointer + 1) % n_frames;     // move FIFO pointer
            faults++;
        }
    }

    printf("\nTotal number of page faults (FIFO): %d\n", faults);

    return 0;
}

/*
Sample Input:

Enter number of frames: 3
Enter length of reference string: 12
Enter the reference string (space-separated page numbers):
7 0 1 2 0 3 0 4 2 3 0 3

Sample Output:

Total number of page faults (FIFO): 10

Explanation:
- Frames = 3, reference string length = 12.
- Using FIFO replacement the program replaces the oldest loaded page on each fault.
*/
