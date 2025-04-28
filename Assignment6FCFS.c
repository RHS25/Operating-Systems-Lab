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
            printf("-- ");  // Empty frame
        else
            printf("%2d ", table_frame[i]);  // Display page number
    }
    printf("||");
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
    printf("Enter reference string\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    int count1 = 0;
    printf("Position of frame table after each request\n");
    
    // Process each page request
    for (i = 0; i < n; i++) {
        printf("Page table after request from %2d || ", pages[i]);
        
        // If the page is not present, replace it in the frame
        if (!present(table_frame, nf, pages[i])) {
            table_frame[pos] = pages[i];
            pos = (pos + 1) % nf;  // Move to the next frame (circularly)
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
