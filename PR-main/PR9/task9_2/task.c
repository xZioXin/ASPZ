#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Спроба читання /etc/shadow:\n");
    
    if (system("sudo cat /etc/shadow 2>&1") == -1) {
        perror("Помилка виконання команди");
        return 1;
    }
    
    return 0;
}