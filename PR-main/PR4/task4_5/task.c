#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_realloc_failure() {
    char *ptr = malloc(100);
    if (!ptr) {
        perror("Initial malloc failed");
        return;
    }
    strcpy(ptr, "Test data");
    printf("Original: %p, data: '%s'\n", (void*)ptr, ptr);

    size_t huge_size = (size_t)-1;
    char *new_ptr = realloc(ptr, huge_size);
    
    if (new_ptr == NULL) {
        perror("realloc failed");
        printf("Original block is still intact: '%s'\n", ptr);
        
        strcat(ptr, " (modified after failed realloc)");
        printf("Modified original: '%s'\n", ptr);
        
        free(ptr);
    } else {
        printf("New block: %p\n", (void*)new_ptr);
        free(new_ptr);
    }
}

int main() {
    printf("Testing realloc failure scenario:\n");
    test_realloc_failure();
    return 0;
}