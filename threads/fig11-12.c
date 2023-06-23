#include <apue.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct foo {
	int id;
	int count;
	pthread_mutex_t lock;
	struct foo *next;
	/* possibly more */
};

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;


struct foo *alloc(int id) {
	struct foo *fp = NULL;

	if ((fp = (struct foo*)malloc(sizeof(struct foo))) == NULL) {
		return fp;
	}
	fp->id = id;
	fp->count = 1;
	if (pthread_mutex_init(&fp->lock, NULL) != 0) {
		free(fp);
		return NULL;
	}
	int idx = HASH(id);
	pthread_mutex_lock(&hashlock);
	fp->next = fh[idx];
	fh[idx] = fp;
	pthread_mutex_lock(&fp->lock);
	pthread_mutex_unlock(&hashlock);
	/* further initialization */
	pthread_mutex_unlock(&fp->lock);
	return fp;
}

void foo_hold(struct foo *fp) {
	pthread_mutex_lock(&fp->lock);
	fp->count++;
	pthread_mutex_unlock(&fp->lock);
}

void foo_find(int id) {
	struct foo *fp;
	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)]; fp != NULL; fp = fp->next) {
		if (fp->id == id) {
			foo_hold(fp);
			break;
		}
	}
	pthread_mutex_unlock(&hashlock);
}

void foo_release(struct foo *fp) {
	struct foo *temp;

	pthread_mutex_lock(&hashlock);
	if (--fp->count == 0) {  // last reference
		int idx = HASH(fp->id);
		temp = fh[idx];
		if (temp == fp) {
			fh[idx] = fp->next;
		} else {
			while (temp->next != fp) {
				temp = temp->next;
			}
			temp->next = fp->next;
		}
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_destroy(&fp->lock);
		free(fp);
	} else {
		pthread_mutex_unlock(&hashlock);
	}
}
