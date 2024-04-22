#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

/*
 * A very simple shell that supports only commands 'exit', 'help', and 'today'.
 */

#define MAX_BUF 160
#define MAX_TOKS 100

int main() {
	int ch;
	char *pos;
	char s[MAX_BUF+2];   // 2 extra for the newline and ending '\0'
	static const char prompt[] = "msh> ";
	char *toks[MAX_TOKS];

	// 
	// YOUR CODE HERE   (add declarations as needed)
	// Two variables for the time.h library. tm short for the struct tm in time.h
	time_t *t;
	struct tm *ti;
	//
	while (1) {
		// prompt for input if input from terminal
		if (isatty(fileno(stdin))) {
			printf(prompt);
		}

		// read input
		char *status = fgets(s, MAX_BUF+2, stdin);

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

		// Get first token separated by spacing
		toks[0] = strtok(s, " ");

		while (toks[0] != NULL) {
			// Seed the times for when the command gets executed.
			time(t);
			ti = localtime(t);

			// Comparing strings in these if statements
			// Prefixing all with ! since false equates to 0
			if (!strcmp(toks[0], "exit")) exit(EXIT_SUCCESS);
			if (!strcmp(toks[0], "help")) printf("Find help on csumb.edu");
			// tm struct starts month at 0 and the year at 1900 so a little math to adjust
			if (!strcmp(toks[0], "today")) printf("It's currently %d/%d/%d", ti->tm_mon+1, ti->tm_mday, ti->tm_year+1900);
			else printf("token: '%s'", toks[0]);

			// Move onto the next token
			toks[0] = strtok(NULL, " ");
			// Newline for sanity
			printf("\n");
		} // Keep looping if it's not empty
	}
	exit(EXIT_SUCCESS);
}
