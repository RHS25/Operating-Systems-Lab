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

// Function to find the position of the page to be replaced using the Optimal policy
int findpos(int table_frame[], int nf, int pages[], int curr, int np) {
    int pos[nf];
    
    // Initialize the position array to a large value
    for (int i = 0; i < nf; i++) {
        pos[i] = 1e9;
    }
    
    // Calculate the next occurrence of each page after the current reference
    for (int i = 0; i < nf; i++) {
        for (int j = curr + 1; j < np; j++) {
            if (pages[j] == table_frame[i]) {
                pos[i] = j;  // Track next occurrence of page
                break;
            }
        }
    }
    
    // Find the page that is not needed in the future (has the furthest next occurrence)
    int max1 = -1, returnpos = -1;
    for (int i = 0; i < nf; i++) {
        if (pos[i] > max1) {
            max1 = pos[i];
            returnpos = i;
        }
    }
    return returnpos;
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
        
        // If the page is not present, replace it using Optimal policy
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
