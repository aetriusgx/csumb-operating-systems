/* 
 * A group of teens and chaperons
 *
 * Teen can't enter room unless a chaperon is present.
 * Chaperon can't leave room if it would mean teens
 * are present without a chaperon.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_MOVES 1000

typedef struct {
  // sync. variables
  pthread_mutex_t lock;
  pthread_cond_t cv_teen_enter;
  pthread_cond_t cv_chap_leave;
  
  // state variables
  int num_chaperons;  // number of chaperons in the room
  int num_teens;      // number of teens in the room
} ROOM;

ROOM *room_create() {
  ROOM *room;
  room = malloc(sizeof(ROOM));
  assert(room != NULL);

  // initialize sync. variables
  pthread_mutex_init(&room->lock, NULL);
  pthread_cond_init(&room->cv_teen_enter, NULL);
  pthread_cond_init(&room->cv_chap_leave, NULL);

  // initialize state variables
  room->num_teens = 0;
  room->num_chaperons = 0;
  
  return(room);
}

void chaperon_enter(ROOM *room) {

  

  room->num_chaperons++;
  printf("ce\n");

  // YOUR CODE HERE

}

void chaperon_leave(ROOM *room) {

  // YOUR CODE HERE

  room->num_chaperons--;
  printf("cl\n");

  // YOUR CODE HERE

}

void teen_enter(ROOM *room) {

  // YOUR CODE HERE

  room->num_teens++;
  printf("te\n");

  // YOUR CODE HERE

}

void teen_leave(ROOM *room) {

  // YOUR CODE HERE

  room->num_teens--;
  printf("tl\n");

  // YOUR CODE HERE

}

// chaperon thread
void *chaperon(void *arg) {
  ROOM *room = (ROOM *)arg;
  
  // chaperons never stop
  while (1) {
    chaperon_enter(room);
    chaperon_leave(room);
  }
}

// teen thread
void *teen(void *arg) {
  ROOM *room = (ROOM *)arg;

  // teens stop after using the room a bunch of times
  int i;
  for (i = 0; i < NUM_MOVES; i++) {
    teen_enter(room);
    teen_leave(room);
  } 
  pthread_exit(NULL); 
}

// test the chaperons and teens
int main(int argc, char *argv[]) {
  pthread_t t1,t2,t3,t4,t5;
  pthread_t c1,c2;

  // create a room
  ROOM *room = room_create();

  // create some teens and chaperons
  pthread_create(&t1, NULL, teen, (void *)room);
  pthread_create(&t2, NULL, teen, (void *)room);
  pthread_create(&t3, NULL, teen, (void *)room);
  pthread_create(&t4, NULL, teen, (void *)room);
  pthread_create(&t5, NULL, teen, (void *)room);

  pthread_create(&c1, NULL, chaperon, (void *)room);
  pthread_create(&c2, NULL, chaperon, (void *)room);

  // wait for the teens to finish
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  pthread_join(t5, NULL);
  exit(0);
}

