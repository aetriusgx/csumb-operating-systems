#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
 * A simple shell
 */

#define MAX_BUF 160
#define MAX_TOKS 100

int main(int argc, char *argv[]) {
    int ch;
    int i;
    char *pos;
    char *tok;
    char s[MAX_BUF+2];   // 2 extra for the newline and ending '\0'
    static const char prompt[] = "msh> ";
    char *toks[MAX_TOKS];
    time_t rawtime;
    struct tm *timeinfo;
    char *path;
    FILE *infile;

    // process command-line arguments
    if (argc > 2) {
        fprintf(stderr, "msh: usage: msh [file]\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 2) {
        // read from script supplied on the command line
        infile = fopen(argv[1], "r");
        if (infile == NULL) {
            fprintf(stderr, "msh: cannot open script '%s'.\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    } else {
        infile = stdin;
    }

    while (1) {
        // prompt for input if input from terminal
        if (isatty(fileno(infile))) {
            printf(prompt);
        }

        // read input
        char *status = fgets(s, MAX_BUF+2, infile);

        // exit if ^d entered
        if (status == NULL) {
            printf("\n");
            break;
        }

        // input is too long if last character is not newline 
        if ((pos = strchr(s, '\n')) == NULL) {
            printf("error: input too long\n");
            // clear the input buffer
            while ((ch = getchar()) != '\n' && ch != EOF) ;
            continue; 
        }

        // remove trailing newline
        *pos = '\0';

        // break input into tokens
        i = 0;
        char *rest = s;
        while ((tok = strtok_r(rest, " ", &rest)) != NULL && i < MAX_TOKS) {
            toks[i] = tok;
            i++;
        }
        if (i == MAX_TOKS) {
            printf("error: too many tokens\n");
            continue;
        }
        toks[i] = NULL;

        // if no tokens do nothing
        if (toks[0] == NULL) {
            continue;
        }

        // exit if command is 'exit'
        if (strcmp(toks[0], "exit") == 0) {
            break;
        }

        // print help info if command is 'help'
        if (strcmp(toks[0], "help") == 0) {
            printf("enter a Linux command, or 'exit' to quit\n");
            continue;
        }

        // print date if command is 'date'
        if (strcmp(toks[0], "today") == 0) {
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            printf("%02d/%02d/%4d\n", 1 + timeinfo->tm_mon, timeinfo->tm_mday, 1900 + timeinfo->tm_year);
            continue;
        }

        // cd command
        if (strcmp(toks[0], "cd") == 0) {
            // cd 
            if (toks[1] == NULL) {
                path = getenv("HOME");
            } else {
                path = toks[1];
            }
            int cd_status = chdir(path);
            if (cd_status != 0) {
                printf("msh: %s: %s: %s\n", toks[0], path, strerror(errno));
            }
            continue;
        }

        // otherwise fork a process to run the command
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        if (rc == 0) {
            for (int c = 0; c < i; c++) {
                if (strcmp(toks[c], "<") == 0) {
                    FILE* f = fopen(toks[c + 1], "r");

                    if (f == NULL) perror("Can't open file.");

                    int fno = fileno(f);

                    for (int j = c; j < i; j++) {
                        toks[j] = toks[j + 1];
                    }
                    for (int j = c; j < i; j++) {
                        toks[j] = toks[j + 1];
                    }
                    i-=2;

                    dup2(fno, STDIN_FILENO);
                    fclose(f);
                }
                if (strcmp(toks[c], ">") == 0) {
                    FILE* f = fopen(toks[c + 1], "w+");

                    if (f == NULL) perror("Can't open file.");

                    int fno = fileno(f);

                    for (int j = c; j < i; j++) {
                        toks[j] = toks[j + 1];
                    }
                    for (int j = c; j < i; j++) {
                        toks[j] = toks[j + 1];
                    }
                    i-=2;

                    dup2(fno, STDOUT_FILENO);
                    fclose(f);
                }
            }
            
            // child process: run the command indicated by toks[0]
            execvp(toks[0], toks);  
            // if execvp returns than an error occurred
            printf("msh: %s: %s\n", toks[0], strerror(errno));
            exit(1);
        } else {
            // wait for command to finish running
            wait(NULL);
        }
    }
    exit(EXIT_SUCCESS);
}
