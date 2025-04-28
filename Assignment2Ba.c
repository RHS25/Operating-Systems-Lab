#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void asc(int *a, int sz);  // Function prototype for ascending sort

int main(int argc, char *argv[]) {
    int arr[10];
    int i, size;
    char *env[] = {NULL};  // Environment for execve (not used here)
    FILE *f;
    char *newarg[] = {NULL, "sort.txt", NULL};  // Arguments for child process

    // Set the file path for newarg[0]
    newarg[0] = argv[1];

    pid_t pid;
    printf("\nEnter size of array: ");
    scanf("%d", &size);  // Read array size

    printf("\nEnter %d elements: \n", size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);  // Read array elements
    }

    pid = fork();  // Fork a child process
    if(pid == 0) {  // In child process
        execve(argv[1], newarg, env);  // Execute child process
    } else {  // In parent process
        asc(arr, size);  // Sort array in ascending order

        // Open the file "sort.txt" for writing
        f = fopen("sort.txt", "w");
        fprintf(f, "%d", size);  // Write size of array
        for(i = 0; i < size; i++) {
            fprintf(f, " %d", arr[i]);  // Write sorted array
        }
        fclose(f);  // Close the file
    }

    return 0;
}

// Function to sort array in ascending order
void asc(int *a, int sz) {
    int i, j, temp;
    // Sorting in ascending order using bubble sort
    for(i = 0; i < sz - 1; i++) {
        for(j = i + 1; j < sz; j++) {
            if(a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    // Print sorted array
    printf("\nParent Process\n");
    printf("Sorted array in ascending order is:\n");
    for(i = 0; i < sz; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
