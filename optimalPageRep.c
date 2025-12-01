//Write a program to calculate the number of page faults for a reference string for optimal page replacement algorithm.

#include <stdio.h>

int main() {
    int n_frames, n_refs;
    int i, j, k, page, faults = 0;

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

    // Initialize frames as empty
    for (i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    // Optimal Page Replacement
    for (i = 0; i < n_refs; i++) {
        page = ref[i];
        int hit = 0;

        // Check if page is already present in frames (HIT?)
        for (j = 0; j < n_frames; j++) {
            if (frames[j] == page) {
                hit = 1;
                break;
            }
        }

        // If MISS → Page Fault
        if (!hit) {
            faults++;

            // Check for empty frame first
            int empty_index = -1;
            for (j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    empty_index = j;
                    break;
                }
            }

            if (empty_index != -1) {
                // Place page in empty frame
                frames[empty_index] = page;
            } else {
                // No empty frame → choose a page to replace optimally
                int farthest_index = -1;
                int farthest_pos = -1;

                for (j = 0; j < n_frames; j++) {
                    int next_use_pos = -1;
                    for (k = i + 1; k < n_refs; k++) {
                        if (ref[k] == frames[j]) {
                            next_use_pos = k;
                            break;
                        }
                    }

                    // If this page is never used again, replace it
                    if (next_use_pos == -1) {
                        farthest_index = j;
                        farthest_pos = n_refs + 1; // max
                        break;
                    }

                    // Choose the page with farthest next use
                    if (next_use_pos > farthest_pos) {
                        farthest_pos = next_use_pos;
                        farthest_index = j;
                    }
                }

                frames[farthest_index] = page;
            }
        }
    }

    printf("\nTotal number of page faults (Optimal): %d\n", faults);

    return 0;
}

/*
Sample Input:

Enter number of frames: 3
Enter length of reference string: 12
Enter the reference string (space-separated page numbers):
7 0 1 2 0 3 0 4 2 3 0 3

Sample Output:

Total number of page faults (Optimal): 7

Explanation:
- Frames = 3, reference string length = 12.
- Optimal replacement chooses the page whose next use is farthest (or not used again).
- For the example reference string the optimal algorithm results in 7 page faults.
*/
