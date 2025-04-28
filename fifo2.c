

#include <stdio.h>                // Include standard I/O library for input and output functions
#include <unistd.h>               // Include POSIX API for various functions, including read and write
#include <fcntl.h>                // Include file control options, for file operations
#include <string.h>               // Include string handling functions for manipulating C strings
#include <sys/stat.h>            // Include definitions for file status and to create FIFOs

// Define the names of the FIFOs for inter-process communication
#define FIFO1 "fifo1"           // FIFO for receiving input from the sender
#define FIFO2 "fifo2"           // FIFO for sending processed output back to the sender

int main() {
    char input[100];             // Buffer to store data read from FIFO1
    char output[100];            // Buffer to store the processed data to send back
    int fifo_fd, fifo2_fd;       // File descriptors for the FIFOs
    int words = 0, lines = 0, characters = 0; // Counters for words, lines, and characters
    FILE *file_ptr;              // File pointer for file operations

    // Open FIFO1 in read-only mode to receive input from the sender process
    fifo_fd = open(FIFO1, O_RDONLY);
    // Read data from FIFO1 into the input buffer
    read(fifo_fd, input, sizeof(input));
    // Close the FIFO file descriptor after reading to release the resource
    close(fifo_fd);
    
    // Display the received message to the user
    printf("Message received from sender:\n%s\n", input);

    // Iterate through each character in the input buffer to count characters, words, and lines
    for (int i = 0; input[i] != '\0'; i++) {
        // Count characters (excluding spaces, newlines, and '#')
        if (input[i] != ' ' && input[i] != '\n' && input[i] != '#') {
            characters++;
        }
        // Count words based on spaces and newlines (considering '#' as an end marker)
        if (input[i] == ' ' || input[i] == '\n' || input[i] == '#') {
            words++;
        }
        // Count lines based on newlines and '#'
        if (input[i] == '\n' || input[i] == '#') {
            lines++;
        }
    }

    // Open a file named "output.txt" in write mode to save the counts
    file_ptr = fopen("output.txt", "w");
    // Write the counts of characters, words, and lines into the output file
    fprintf(file_ptr, "Characters: %d\nWords: %d\nLines: %d\n", characters, words, lines);
    // Close the file after writing the results to free resources
    fclose(file_ptr);

    // Open the output file in read mode to read the results into the output buffer
    file_ptr = fopen("output.txt", "r");
    // Read the contents of the output file into the output buffer
    fread(output, sizeof(char), sizeof(output), file_ptr);
    // Close the file after reading
    fclose(file_ptr);

    // Create FIFO2 if it does not already exist, with read and write permissions for all
    mkfifo(FIFO2, 0666);

    // Open FIFO2 in write-only mode to send the processed data back to the sender
    fifo2_fd = open(FIFO2, O_WRONLY);
    // Write the output buffer containing the results to FIFO2, including the null terminator
    write(fifo2_fd, output, strlen(output) + 1);
    // Inform the user that the processed data has been sent to the sender
    printf("Processed data sent to sender.\n");

    // Close FIFO2 after sending the data to free resources
    close(fifo2_fd);

    return 0;                     // Return success status
}
