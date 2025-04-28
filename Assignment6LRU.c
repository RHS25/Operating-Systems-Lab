#include<stdio.h>

// Function to check if a page is already present in the frame
int present(int table_frame[], int nf, int page) {
    for (int i = 0; i < nf; i++) {
        if (page == table_frame[i]) {
            return 1;  // Page found
        }
    }
    return 0;  // Page not found
}

// Function to print the current page table
void printtable(int table_frame[], int nf) {
    for (int i = 0; i < nf; i++) {
        if (table_frame[i] == -1)
            printf("-- ");
        else
            printf("%2d ", table_frame[i]);
    }
    printf("||");
}

// Function to find the position of the page to be replaced
int findpos(int table_frame[], int nf, int pages[], int curr, int np) {
    for (int i = 0; i < nf; i++) {
        if (table_frame[i] == -1) {
            return i;  // Empty frame available
        }
    }
    
    int pos[nf];
    
    // Calculate the position of the next occurrence of each page
    for (int i = 0; i < nf; i++) {
        pos[i] = -1e9;
        for (int j = curr - 1; j >= 0; j--) {
            if (pages[j] == table_frame[i]) {
                pos[i] = j;  // Track the last used time of each page
                break;
            }
        }
    }
    
    // Find the least recently used page to replace
    int min1 = 1000000, retPos = -1;
    for (int i = 0; i < nf; i++) {
        if (min1 > pos[i]) {
            min1 = pos[i];
            retPos = i;
        }
    }
    return retPos;
}

int main() {
    int n, nf, i, pos = 0;
    
    // Input number of frames
    printf("Enter number of frames\n");
    scanf("%d", &nf);
    
    // Initialize frame table with -1 (empty frames)
    int table_frame[nf];
    for (i = 0; i < nf; i++) {
        table_frame[i] = -1;
    }
    
    // Input total number of page requests
    printf("Enter total number of page requests\n");
    scanf("%d", &n);
    
    // Input page reference string
    int pages[n];
    printf("Enter pages\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    int count1 = 0;
    printf("Position of frame table after each request\n");
    
    // Process each page request
    for (i = 0; i < n; i++) {
        printf("Page table after request from %2d || ", pages[i]);
        
        // If the page is not present, replace it using LRU policy
        if (!present(table_frame, nf, pages[i])) {
            int pos = findpos(table_frame, nf, pages, i, n);
            table_frame[pos] = pages[i];
            printtable(table_frame, nf);
            printf("Page fault\n");
            count1++;
            continue;
        }
        printtable(table_frame, nf);
        printf("\n");
    }
    
    // Output the total number of page faults
    printf("\nNumber of page faults: %d\n\n", count1);
}
