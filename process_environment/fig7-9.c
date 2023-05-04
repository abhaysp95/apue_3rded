#include <apue.h>
#include <stdio.h>
#include <setjmp.h>

#define TOK_ADD 5

void do_line(char *);
void cmd_add(void);
int get_token(void);

jmp_buf jumpbuffer;

int main(void) {
	char line[MAXLINE];

	if (setjmp(jumpbuffer) != 0) {
		printf("error");
	}  // then proceed with processing next line
	while (fgets(line, MAXLINE, stdin) != NULL) {
		do_line(line);
	}

	exit(0);
}

char *tok_ptr;

void do_line(char *ptr) {
	int cmd;

	tok_ptr = ptr;
	while ((cmd = get_token()) > 0) {
		switch (cmd) {
			case TOK_ADD:
				cmd_add();
				break;
		}
	}
}

void cmd_add() {
	int token = 0;
	token = get_token();
	if (token < 0) {
		longjmp(jumpbuffer, 1);
	}

	// processing of this command
}

int get_token() {
	// fetch next token from line pointed to by tok_ptr

	return 5;
}
