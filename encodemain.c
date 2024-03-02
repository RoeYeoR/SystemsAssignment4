#include "compress.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -c <input_file> or %s -d <input_file>\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // Determine operation mode
    int compress_mode = 0;
    if (strcmp(argv[1], "-c") == 0) {
        compress_mode = 1;
    } else if (strcmp(argv[1], "-d") != 0) {
        fprintf(stderr, "Error: Invalid mode. Use -c to compress or -d to decompress.\n");
        return EXIT_FAILURE;
    }

    // Call appropriate function based on mode
    if (compress_mode) {
        compress_file(argv[2]);
    } else {
        decompress_file(argv[2]);
    }

    return EXIT_SUCCESS;
}
