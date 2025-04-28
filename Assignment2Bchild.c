#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void desc(int *a, int sz);  // Function prototype for descending sort

int main(int argc, char *argv[]) {
    int arr[10], i, size;
    FILE *f;

    // Open the file passed as an argument (i.e., sort.txt)
    f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("File opening failed");
        return 1;
    }

    // Read the size of the array from the file
    fscanf(f, "%d", &size);
    printf("Array Size is: %d\n", size);

    // Read the elements of the array from the file
    for(i = 0; i < size; i++) {
        fscanf(f, " %d", &arr[i]);
        printf("%d ", arr[i]);  // Print elements as they are read
    }
    printf("\n");

    // Sort the array in descending order
    desc(arr, size);

    fclose(f);  // Close the file

    return 0;
}

// Function to sort array in descending order
void desc(int *a, int sz) {
    int i, j, temp;
    // Sorting in descending order using bubble sort
    for(i = 0; i < sz - 1; i++) {
        for(j = i + 1; j < sz; j++) {
            if(a[i] < a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    // Print sorted array
    printf("\nChild Process\n");
    printf("Sorted array in descending order is:\n");
    for(i = 0; i < sz; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
