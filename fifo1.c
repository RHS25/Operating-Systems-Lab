

#include <stdio.h>                // Include standard I/O library for input and output functions
#include <unistd.h>               // Include POSIX API for various functions, including read and write
#include <fcntl.h>                // Include file control options for file operations
#include <string.h>               // Include string handling functions for manipulating C strings
#include <sys/stat.h>            // Include definitions for file status and to create FIFOs

// Define the names of the FIFOs for inter-process communication
#define FIFO1 "fifo1"           // FIFO for sending input to the receiver
#define FIFO2 "fifo2"           // FIFO for receiving processed output from the receiver

int main() {
    char input[100];            // Buffer to store user input
    char output[100];           // Buffer to store the message received from the receiver
    int fifo_fd, fifo2_fd;      // File descriptors for the FIFOs

    // Prompt the user to enter a string ending with '#'
    printf("Enter a string ending with '#':\n");
    int i = 0;                  // Initialize index for input buffer
    char ch;                   // Variable to store each character input
    // Read characters from standard input until '#' is encountered
    while ((ch = getchar()) != '#') {
        input[i++] = ch;        // Store each character in the input buffer
    }
    input[i] = '\0';            // Null-terminate the string to mark the end

    // Create FIFO1 if it does not already exist, with read and write permissions for all
    mkfifo(FIFO1, 0666);

    // Open FIFO1 in write-only mode to send the input to the receiver
    fifo_fd = open(FIFO1, O_WRONLY);
    // Write the user input to FIFO1, including the null terminator
    write(fifo_fd, input, strlen(input) + 1);
    // Inform the user that the message has been sent to the receiver
    printf("Message sent to receiver.\n");

    // Close FIFO1 after writing to free resources
    close(fifo_fd);

    // Open FIFO2 in read-only mode to receive processed data from the receiver
    fifo2_fd = open(FIFO2, O_RDONLY);
    // Read the processed data from FIFO2 into the output buffer
    read(fifo2_fd, output, sizeof(output));
    // Display the received processed data to the user
    printf("Received from receiver:\n%s\n", output);

    // Close FIFO2 after reading to free resources
    close(fifo2_fd);

    return 0;                    // Return success status
}
