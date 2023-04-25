#include <apue.h>
#include <bits/types/FILE.h>
#include <stdio.h>

void pr_stdio(const char* name, FILE *fp);
int is_unbuffered(FILE *fp);
int is_line_buffered(FILE *fp);
int buffer_size(FILE *fp);

int main(void) {
	FILE *fp = NULL;

	fputs("enter any character\n", stdout);
	if (getchar() == EOF) {  // equivalent to getc(stdin)
		err_sys("getchar error");
	}
	fputs("enter one line\n", stderr);

	pr_stdio("stdio", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/passwd", "r")) == NULL) {
		err_sys("fopen error");
	}
	if (getc(fp) == EOF) {
		err_sys("getc error");
	}
	pr_stdio("/etc/passwd", fp);

	return 0;
}

void pr_stdio(const char *name, FILE *fp) {
	printf("stream = %s, ", name);
	if (is_unbuffered(fp)) {
		printf("unbuffered");
	} else if(is_line_buffered(fp)) {
		printf("line buffered");
	} else {
		printf("fully buffered");
	}
	printf(", buffer_size = %d\n", buffer_size(fp));
}

// non-protable
#if defined (_IO_UNBUFFERED)
int is_unbuffered(FILE *fp) {
	return (fp->_flags & _IO_UNBUFFERED);
}

int is_line_buffered(FILE *fp) {
	return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp) {
	return (fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined (__SNBF)

int is_unbuffered(FILE *fp) {
	return (fp->_flags & __SNBF);
}

int is_line_buffered(FILE *fp) {
	return (fp->_flags & __SLBF);
}

int buffer_size(FILE *fp) {
	return (fp->_bf._size);
}

#elif defined (_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr _IO_buf_end
#define _base _IO_buf_base
#endif /* ifdef _LP64 */

int is_unbuffered(FILE *fp) {
	return (fp->_flags & _IONBF);
}

int is_line_buffered(FILE *fp) {
	return (fp->_flags & _IOLBF);
}

int buffer_size(FILE *fp) {
#ifdef _LP64
	return (fp->_ptr - fp->_base);
#endif
	return BUFSIZ;
}

#else

#error unknown stdio implementation!

#endif
