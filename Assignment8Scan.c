#include <stdio.h>
#include <stdlib.h>

int absoluteValue(int x) {
    return (x > 0) ? x : -x;
}

void main() {
    int queue[25], n, headposition, i, j, seek = 0;
    float averageSeekTime;
    
    // Reading the maximum range of the disk
    printf("Enter the maximum range of Disk: ");
    int maxrange;
    scanf("%d", &maxrange);
    
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
    
    // Sort the queue in ascending order
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (queue[i] > queue[j]) {
                int temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }
    
    // Find the first request greater than the current head position
    int index = 0;
    while (index < n && queue[index] < headposition) {
        index++;
    }
    
    // Move towards the right (serve requests greater than the head position)
    for (i = index; i < n; i++) {
        seek += absoluteValue(headposition - queue[i]);
        printf("Disk head moves from %d to %d with Seek %d\n", headposition, queue[i], absoluteValue(headposition - queue[i]));
        headposition = queue[i];
    }
    
    // Now move in the reverse direction to serve any remaining requests on the left side
    for (i = index - 1; i >= 0; i--) {
        seek += absoluteValue(headposition - queue[i]);
        printf("Disk head moves from %d to %d with Seek %d\n", headposition, queue[i], absoluteValue(headposition - queue[i]));
        headposition = queue[i];
    }
    
    // Calculating the average seek time
    averageSeekTime = seek / (float)n;
    
    // Display the total and average seek times
    printf("Total Seek Time = %d\n", seek);
    printf("Average Seek Time = %f\n", averageSeekTime);
}
