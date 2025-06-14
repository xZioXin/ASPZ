#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    struct passwd *pw;
    uid_t my_uid = getuid();
    int min_uid = 1000;
    
    printf("Звичайні користувачі (UID >= %d, крім вас %d):\n", min_uid, my_uid);
    
    while ((pw = getpwent()) != NULL) {
        if (pw->pw_uid >= min_uid && pw->pw_uid != my_uid) {
            printf("%s (UID: %d, GID: %d, Shell: %s)\n", 
                   pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_shell);
        }
    }
    
    endpwent();
    return 0;
}