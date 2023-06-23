#include <apue.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct foo *fh[NHASH];

// static mutex intiialization (for fh)
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int count;
	int id;
	pthread_mutex_t lock;
	struct foo *next;
};

// allocation of object
struct foo *foo_alloc(int id) {
	struct foo *fp = NULL;
	if ((fp = (struct foo*)malloc(sizeof(struct foo))) == NULL) {
		return fp;  // return NULL
	}

	fp->count = 1;
	fp->id = id;
	if (pthread_mutex_init(&fp->lock, NULL) != 0) {
		free(fp);
		return NULL;
	}

	int idx = HASH(id);
	pthread_mutex_lock(&hashlock);
	fp->next = fh[idx];  // should be NULL, right
	fh[idx] = fp;
	// now another thread can use this new fp, from fh, thus lock is necessary
	pthread_mutex_lock(&fp->lock);
	pthread_mutex_unlock(&hashlock);
	// continue intiialization
	pthread_mutex_unlock(&fp->lock);

	return fp;
}

// add reference to object
void foo_hold(struct foo *fp) {
	pthread_mutex_lock(&fp->lock);
	fp->count++;
	pthread_mutex_unlock(&fp->lock);
}

// find the existing object
struct foo *foo_find(int id) {
	struct foo *fp;
	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)]; fp != NULL; fp = fp->next) {
		if (fp->id == id) {
			foo_hold(fp);
			break;
		}
	}

	pthread_mutex_unlock(&hashlock);
	return fp;
}

// release a reference to the object
void foo_release(struct foo *fp) {
	struct foo *temp;

	pthread_mutex_lock(&fp->lock);
	// if last reference
	if (fp->count == 1) {
		pthread_mutex_unlock(&fp->lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->lock);
		if (fp->count != 1) {
			fp->count--;
			pthread_mutex_unlock(&fp->lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		// remove from list
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
		pthread_mutex_unlock(&fp->lock);
		pthread_mutex_destroy(&fp->lock);
		free(fp);
	} else {
		fp->count--;
		pthread_mutex_unlock(&fp->lock);
	}
}
