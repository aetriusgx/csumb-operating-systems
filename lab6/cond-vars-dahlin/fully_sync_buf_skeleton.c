
/* 
 * A fully-synchronized buffer.
 * An fsbuf_write() call will not return until the written
 * value has been read.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  // sync vars
  pthread_mutex_t lock;
  pthread_cond_t read_go;
  pthread_cond_t write_go;
  // YOUR CODE HERE (add more condition variables if you wish)

  // state vars
  int buf;
  int count;
} FSBUF;

FSBUF *fsbuf_create() {
  FSBUF *fsbuf = (FSBUF *)malloc(sizeof(FSBUF));

  pthread_mutex_init(&fsbuf->lock, NULL);
  pthread_cond_init(&fsbuf->read_go, NULL);
  pthread_cond_init(&fsbuf->write_go, NULL);
  // YOUR CODE HERE (initialize new cond. variables if needed)

  fsbuf->count = 0;

  return fsbuf;
}

int fsbuf_read(FSBUF *fsbuf) {
    pthread_mutex_lock(&fsbuf->lock);

    // wait for the buffer to contain something
    while (fsbuf->count != 1) {
      pthread_cond_wait(&fsbuf->read_go, &fsbuf->lock);
    }

    // do the read
    fsbuf->count = 0;
    int val = fsbuf->buf;

    // let other threads know about it
    pthread_cond_signal(&fsbuf->write_go);

    // YOUR CODE HERE

    pthread_mutex_unlock(&fsbuf->lock);
    return(val);
}

void fsbuf_write(FSBUF *fsbuf, int val) {
    pthread_mutex_lock(&fsbuf->lock);
    
    // wait for buffer to become empty
    while (fsbuf->count != 0) {
      pthread_cond_wait(&fsbuf->write_go, &fsbuf->lock);
    }

    // do the write
    fsbuf->count = 1;
    fsbuf->buf = val;

    // let other threads know about it
    pthread_cond_signal(&fsbuf->read_go);
 
    // wait for written value to be read
    // YOUR CODE HERE

    pthread_mutex_unlock(&fsbuf->lock);
}

void *reader(void *arg) {
  FSBUF *fsbuf = (FSBUF *)arg;
  int i;
  int val;
  for (i = 0; i < 100; i++) {
    val = fsbuf_read(fsbuf);
    printf("R: %d\n", val);
  } 
  pthread_exit(NULL);
}

void *writer(void *arg) {
  FSBUF *fsbuf = (FSBUF *)arg;
  int i;
  for (i = 0; i < 100; i++) {
    fsbuf_write(fsbuf, i);
    printf("W: %d\n", i);
  } 
  pthread_exit(NULL);
}

// run reader and writer
int main(int argc, char *argv[]) {
  pthread_t p1, p2, p3, p4;
  FSBUF *fsbuf = fsbuf_create();
  pthread_create(&p1, NULL, reader, (void *)fsbuf);
  pthread_create(&p2, NULL, reader, (void *)fsbuf);
  pthread_create(&p3, NULL, writer, (void *)fsbuf);
  pthread_create(&p4, NULL, writer, (void *)fsbuf);

  pthread_exit(NULL);
}
