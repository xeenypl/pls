#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv) {
    struct passwd *u = getpwnam("root");
    if (argc < 2) {
        fputs("usage: pls [command]\n", stderr);
        return 1;
    }
    if (setuid(u -> pw_uid) < 0) {
        perror("setuid");
        return 2;
    }
    execvp(argv[1], argv + 1);
    perror("execvp");
    return 2;
}
