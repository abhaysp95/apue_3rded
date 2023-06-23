#include <apue.h>
#include <pthread.h>

struct foo {
	int count;
	int id;
	pthread_mutex_t mutex;
	/** other fields */
};

struct foo *alloc(int id) {
	struct foo *foo = NULL;
	if ((foo = (struct foo *)malloc(sizeof(struct foo))) == NULL) {
		foo->id = id;
		foo->count = 0;
		if (pthread_mutex_init(&foo->mutex, NULL /* attributes */) != 0) {
			free(foo);
			return NULL;
		}
		/** continue initialization */
	}

	return foo;
}

void foo_hold(struct foo *foo) {
	pthread_mutex_lock(&foo->mutex);
	foo->count++;
	pthread_mutex_unlock(&foo->mutex);
}

void foo_release(struct foo *foo) {
	pthread_mutex_lock(&foo->mutex);
	if (foo->count == 0) {  // last reference
		pthread_mutex_unlock(&foo->mutex);
		pthread_mutex_destroy(&foo->mutex);
		free(foo);
	} else {
		foo->count--;
		pthread_mutex_unlock(&foo->mutex);
	}
}
