#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>
#include <termios.h>

void check_pass(void) {
    int i = 0;
    struct termios oldt, newt;
    struct spwd* spwd = getspnam(getlogin());
    char passwd[512] = { 0 };
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    for (;; i++) {
        fputs("password:", stderr);
        fgets(passwd, sizeof(passwd), stdin);
        *(strchr(passwd, '\n')) = 0;
        if (strcmp(spwd->sp_pwdp, crypt(passwd, spwd->sp_pwdp)) == 0) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fputs("\n", stderr);
            return;
        }
        if (i < 3) break;
        fputs("\nWrong password try again\n", stderr);
    }
    fputs("\nWrong password\n", stderr);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    exit(1);
}

int main (int argc, char **argv) {
    struct passwd *u = getpwnam("root");
    if (argc < 2) {
        fputs("usage: pls [command]\n", stderr);
        return 1;
    }
    check_pass();
    if (setuid(u -> pw_uid) < 0) {
        perror("setuid");
        return 2;
    }
    execvp(argv[1], argv + 1);
    perror("execvp");
    return 2;
}
