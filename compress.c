#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_file(const char *filename) {
    // Open the input file
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Unable to open input file\n");
        exit(EXIT_FAILURE);
    }

    // Generate output filename
    char output_filename[strlen(filename) + 5]; // 5 for ".bin\0"
    strcpy(output_filename, filename);
    strcat(output_filename, ".bin");

    // Open the output file
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to create output file\n");
        exit(EXIT_FAILURE);
    }

    // Process each digit from the input file
    int digit;
    while ((digit = fgetc(input_file)) != EOF) {
        // Ensure digit is within the range '0' to '9'
        if (digit < '0' || digit > '9') {
            fprintf(stderr, "Error: Input file contains invalid characters\n");
            exit(EXIT_FAILURE);
        }

        // Convert digit to its integer value
        int value = digit - '0';

        // Perform bitwise reversal
        int reversed = 0;
        for (int i = 0; i < 4; i++) {
            reversed |= ((value >> i) & 1) << (3 - i);
        }

        // Write the reversed digit to the output file
        fwrite(&reversed, sizeof(char), 1, output_file);
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Compression successful. Output file: %s\n", output_filename);
}

void decompress_file(const char *filename) {
    // Open the input file
    FILE *input_file = fopen(filename, "rb");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Unable to open input file\n");
        exit(EXIT_FAILURE);
    }

    // Generate output filename
    char output_filename[strlen(filename) - 4]; // Remove ".bin"
    strncpy(output_filename, filename, strlen(filename) - 4);
    output_filename[strlen(filename) - 4] = '\0'; // Null-terminate string

    // Open the output file
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to create output file\n");
        exit(EXIT_FAILURE);
    }

    // Process each byte from the input file
    int byte;
    while ((byte = fgetc(input_file)) != EOF) {
        // Perform bitwise reversal to retrieve the original digit
        int value = 0;
        for (int i = 0; i < 4; i++) {
            value |= ((byte >> i) & 1) << (3 - i);
        }

        // Convert value to character and write to output file
        fprintf(output_file, "%d", value);
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Decompression successful. Output file: %s\n", output_filename);
}
