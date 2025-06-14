#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_FILE_SIZE (1024 * 1024 * 1024)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL) {
        fprintf(stderr, "Cannot open file %s for reading\n", argv[1]);
        return 2;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL) {
        fclose(src);
        fprintf(stderr, "Cannot open file %s for writing\n", argv[2]);
        return 3;
    }

    char buffer[4096];
    size_t bytes_read;
    size_t total_bytes = 0;
    int error = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        total_bytes += bytes_read;
        
        if (total_bytes > MAX_FILE_SIZE) {
            fprintf(stderr, "File size limit exceeded (max %d bytes)\n", MAX_FILE_SIZE);
            error = 4;
            break;
        }

        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            fprintf(stderr, "Error writing to file %s\n", argv[2]);
            error = 5;
            break;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "Error reading from file %s\n", argv[1]);
        error = 6;
    }

    fclose(src);
    fclose(dst);

    if (error != 0) {
        remove(argv[2]);
        return error;
    }

    return 0;
}