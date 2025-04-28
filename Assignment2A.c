 #include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void asc(int *a, int sz);
void desc(int *a, int sz);

int main() {
    int arr[10];
    int i, size;
    pid_t pid;

    printf("\nEnter size of array: ");
    scanf("%d", &size);

    printf("\nEnter %d elements: \n", size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    pid = fork();  // Forking the process

    if(pid == 0) { // Child process
        desc(arr, size); // Sort array in descending order
        // exit(0); // exit() is not strictly necessary since the child will return after finishing
    }
    else if(pid > 0) {  // Parent process
        wait(NULL);  // Wait for the child process to finish
        asc(arr, size); // Sort array in ascending order
    }
    else {
        // Error handling in case fork fails
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}

void asc(int *a, int sz) {
    int i, j, temp;

    // Sorting in ascending order
    for(i = 0; i < sz - 1; i++) {
        for(j = i + 1; j < sz; j++) {
            if(a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("\nParent Process:\n");
    printf("Sorted array in ascending order is:\n");
    for(i = 0; i < sz; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

void desc(int *a, int sz) {
    int i, j, temp;

    // Sorting in descending order
    for(i = 0; i < sz - 1; i++) {
        for(j = i + 1; j < sz; j++) {
            if(a[i] < a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("\nChild Process:\n");
    printf("Sorted array in descending order is:\n");
    for(i = 0; i < sz; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
