#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#define ALLOWED_USER "root"
#define ALLOWED_GROUP "admin"

int should_free_memory() {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw == NULL) {
        perror("getpwuid");
        return 0;
    }

    if (strcmp(pw->pw_name, ALLOWED_USER) == 0) {
        return 1;
    }

    gid_t gid = getgid();
    struct group *gr = getgrgid(gid);
    if (gr != NULL && strcmp(gr->gr_name, ALLOWED_GROUP) == 0) {
        return 1;
    }

    int ngroups = 0;
    getgrouplist(pw->pw_name, gid, NULL, &ngroups);
    gid_t *groups = malloc((size_t)ngroups * sizeof(gid_t));
    if (groups == NULL) {
        perror("malloc");
        return 0;
    }

    if (getgrouplist(pw->pw_name, gid, groups, &ngroups) == -1) {
        perror("getgrouplist");
        free(groups);
        return 0;
    }

    for (int i = 0; i < ngroups; i++) {
        gr = getgrgid(groups[i]);
        if (gr != NULL && strcmp(gr->gr_name, ALLOWED_GROUP) == 0) {
            free(groups);
            return 1;
        }
    }

    free(groups);
    return 0;
}

int main() {
    int *data = malloc(1024 * sizeof(int));
    if (data == NULL) {
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < 1024; i++) {
        data[i] = i;
    }

    if (should_free_memory()) {
        printf("Freeing memory (user/group allowed)\n");
        free(data);
    } else {
        printf("Not freeing memory (user/group not allowed)\n");
    }

    return 0;
}