#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256

typedef struct {
    unsigned char ch;
    int freq;
} CharFreq;

int compare(const void *a, const void *b) {
    CharFreq *fa = (CharFreq *)a;
    CharFreq *fb = (CharFreq *)b;
    return fb->freq - fa->freq;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    int freq[ASCII_SIZE] = {0};
    int c;

    while ((c = fgetc(file)) != EOF) {
        freq[(unsigned char)c]++;
    }

    CharFreq table[ASCII_SIZE];
    int count = 0;

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            table[count].ch = (unsigned char)i;
            table[count].freq = freq[i];
            count++;
        }
    }

    qsort(table, count, sizeof(CharFreq), compare);

    printf("Символ\tЧастота\n");
    for (int i = 0; i < count; i++) {
        if (table[i].ch == '\n') {
            printf("\\n\t%d\n", table[i].freq);
        } else if (table[i].ch == '\t') {
            printf("\\t\t%d\n", table[i].freq);
        } else if (table[i].ch == ' ') {
            printf("' '\t%d\n", table[i].freq);
        } else {
            printf("%c\t%d\n", table[i].ch, table[i].freq);
        }
    }

    return 0;
}