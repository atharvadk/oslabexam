//Write a program to calculate the number of page faults for a reference string for LRU page replacement algorithm.

#include <stdio.h>

int main() {
    int n_frames, n_refs;
    int i, j, page, faults = 0;
    
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n_refs);

    int ref[n_refs];
    int frames[n_frames];
    int last_used[n_frames];  // to track when each frame was last used

    // Input reference string
    printf("Enter the reference string (space-separated page numbers):\n");
    for (i = 0; i < n_refs; i++) {
        scanf("%d", &ref[i]);
    }

    // Initialize frames as empty
    for (i = 0; i < n_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int time = 0;  // logical time counter

    // LRU Page Replacement
    for (i = 0; i < n_refs; i++) {
        page = ref[i];
        time++;

        int hit = 0;
        int hit_index = -1;

        // Check if page is already in any frame (HIT?)
        for (j = 0; j < n_frames; j++) {
            if (frames[j] == page) {
                hit = 1;
                hit_index = j;
                break;
            }
        }

        if (hit) {
            // Update last used time for this frame
            last_used[hit_index] = time;
        } else {
            // MISS → Page Fault
            faults++;

            // Find an empty frame first
            int empty_index = -1;
            for (j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    empty_index = j;
                    break;
                }
            }

            if (empty_index != -1) {
                // Put page in empty frame
                frames[empty_index] = page;
                last_used[empty_index] = time;
            } else {
                // No empty frame → replace LRU page
                int lru_index = 0;
                int min_time = last_used[0];
                for (j = 1; j < n_frames; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        lru_index = j;
                    }
                }
                frames[lru_index] = page;
                last_used[lru_index] = time;
            }
        }
    }

    printf("\nTotal number of page faults (LRU): %d\n", faults);

    return 0;
}
