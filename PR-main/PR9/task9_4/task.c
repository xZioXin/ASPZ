#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

int main() {
    printf("Поточний користувач: ");
    system("whoami");

    printf("\nІнформація про користувача:\n");
    system("id");

    printf("\nГрупи користувача:\n");
    gid_t groups[100];
    int ngroups = getgroups(100, groups);
    
    for (int i = 0; i < ngroups; i++) {
        struct group *gr = getgrgid(groups[i]);
        printf("%d (%s)\n", groups[i], gr ? gr->gr_name : "?");
    }

    return 0;
}