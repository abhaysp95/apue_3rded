#include <apue.h>
#include <stdio.h>
#include <string.h>

#define SZ 48

int main(void) {
	FILE *fp;
	char buf[SZ];

	// overwrite the buffer with a's
	memset(buf, 'a', SZ-2);
	buf[SZ-2] = '\0';
	buf[SZ-1] = 'X';  // after null byte char

	if ((fp = fmemopen(buf, SZ, "w+")) == NULL) {
		err_sys("fmemopen failed");
	}

	// fmemopen places a null byte at begining
	printf("initial buffer contents: %s\n", buf);
	fprintf(fp, "hello, world");

	// buffer is unchanged until stream is flushed
	printf("before fflush: %s\n", buf);
	fflush(fp);
	printf("after fflush: %s\n", buf);
	// null byte added to end of string
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	// overwrite buffer with b's
	memset(buf, 'b', SZ-2);
	buf[SZ-2] = '\0';
	buf[SZ-1] = 'X';  // after null byte char
	fprintf(fp, "hello, world");
	// fseek causes flush
	fseek(fp, 0, SEEK_SET);
	printf("after fseek: %s\n", buf);
	// null byte placed
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	// overwrite buf with c's
	memset(buf, 'c', SZ-2);
	buf[SZ-2] = '\0';
	buf[SZ-1] = 'X';
	fprintf(fp, "hello, world");
	fclose(fp);
	printf("after fclose: %s\n", buf);
	// no null byte appended
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	exit(0);
}
