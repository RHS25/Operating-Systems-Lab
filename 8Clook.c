#include <stdio.h>

int absoluteValue(int); // Declaring function absoluteValue

void main() {
    int queue[25], n, headposition, i, j, seek = 0, maxrange;
    int difference, temp, queue1[20], queue2[20], temp1 = 0, temp2 = 0;
    float averageSeekTime;

    // Reading the maximum range of the disk
    printf("Enter the maximum range of Disk: ");
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
        scanf("%d", &temp);

        // Separate requests based on their positions relative to head
        if (temp > headposition) {
            queue1[temp1] = temp; // Requests greater than head
            temp1++;
        } else {
            queue2[temp2] = temp; // Requests less than head
            temp2++;
        }
    }

    // Sort queue1[] in ascending order (to process requests after the head position)
    for (i = 0; i < temp1 - 1; i++) {
        for (j = i + 1; j < temp1; j++) {
            if (queue1[i] > queue1[j]) {
                temp = queue1[i];
                queue1[i] = queue1[j];
                queue1[j] = temp;
            }
        }
    }

    // Sort queue2[] in ascending order (to process requests in the wrap-around)
    for (i = 0; i < temp2 - 1; i++) {
        for (j = i + 1; j < temp2; j++) {
            if (queue2[i] > queue2[j]) {
                temp = queue2[i];
                queue2[i] = queue2[j];
                queue2[j] = temp;
            }
        }
    }

    // Start serving requests from the initial head position
    printf("Disk head starts at position %d\n", headposition);

    // Process queue1[] requests first (those greater than the head position)
    for (i = 0; i < temp1; i++) {
        difference = absoluteValue(headposition - queue1[i]);
        seek += difference;
        printf("Disk head moves from position %d to %d with Seek %d\n", headposition, queue1[i], difference);
        headposition = queue1[i];
    }

    // Wrap around to the smallest request in queue2[] if there are requests remaining
    if (temp2 > 0) {
        difference = absoluteValue(headposition - queue2[0]);
        seek += difference;
        printf("Disk head wraps around from position %d to %d with Seek %d\n", headposition, queue2[0], difference);
        headposition = queue2[0];

        // Process remaining requests in queue2[]
        for (i = 1; i < temp2; i++) {
            difference = absoluteValue(headposition - queue2[i]);
            seek += difference;
            printf("Disk head moves from position %d to %d with Seek %d\n", headposition, queue2[i], difference);
            headposition = queue2[i];
        }
    }

    // Calculating the average seek time
    averageSeekTime = seek / (float)n;

    // Display the total and average seek times
    printf("Total Seek Time = %d\n", seek);
    printf("Average Seek Time = %f\n", averageSeekTime);
}

// Function to calculate the absolute value of an integer
int absoluteValue(int x) {
    return (x > 0) ? x : -x;
}
