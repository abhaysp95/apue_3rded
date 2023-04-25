#include <apue.h>
#include <bits/types/FILE.h>
#include <stdio.h>

int main(void) {
	char name[L_tmpnam], line[MAXLINE];

	printf("%s\n", tmpnam(NULL)); // points to static area filled with temp name
								  // (can overwrite that area on subsequent call)

	tmpnam(name);
	printf("name: %s\n", name);

	FILE *fp;
	if ((fp = tmpfile()) == NULL) {  // opens in "rb+" mode
		err_sys("tmpfile error");
	}
	fputs("one line output\n", fp);
	rewind(fp);  // go back to start
	if (fgets(line, sizeof(line), fp) == NULL) {
		err_sys("fgets error");
	}
	fputs(line, stdout);

	exit(0);
}
