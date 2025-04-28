#include <stdio.h>
#include <stdlib.h>

int absoluteValue(int x) {
    return (x > 0) ? x : -x;
}

void main() {
    int queue[25], n, headposition, i, j, seek = 0, minSeek, minIndex;
    float averageSeekTime;
    int visited[25] = {0}; // Track visited requests to avoid re-visiting

    // Reading the number of queue requests (disk access requests)
    printf("Enter the number of queue requests: ");
    scanf("%d", &n);

    // Reading the initial head position (starting point of execution)
    printf("Enter the initial head position: ");
    scanf("%d", &headposition);

    // Reading disk positions to be read in the order of arrival
    printf("Enter the disk positions to be read (queue): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    // Process each request in SSTF order
    printf("Disk head starts at position %d\n", headposition);

    for (i = 0; i < n; i++) {
        minSeek = 10000; // Set a high initial value for minimum seek time
        minIndex = -1;

        // Find the nearest unvisited request
        for (j = 0; j < n; j++) {
            if (!visited[j]) { // Only consider unvisited requests
                int currentSeek = absoluteValue(headposition - queue[j]);
                if (currentSeek < minSeek) {
                    minSeek = currentSeek;
                    minIndex = j;
                }
            }
        }

        // Move the head to the nearest request
        visited[minIndex] = 1; // Mark the request as visited
        seek += minSeek;
        printf("Disk head moves from position %d to %d with Seek %d\n", headposition, queue[minIndex], minSeek);
        headposition = queue[minIndex];
    }

    // Calculating the average seek time
    averageSeekTime = seek / (float)n;

    // Display the total and average seek times
    printf("Total Seek Time = %d\n", seek);
    printf("Average Seek Time = %f\n", averageSeekTime);
}
