/* 
 * Test the dict class
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dict.h"

#define NUM_TESTS 10000

// use the dict
void *use_dict1(void *arg) {
	DICT *dict = (DICT *)arg;

	int i;
	for (i = 0; i < NUM_TESTS; i++) {
		dict_set(dict, "a", "foo");
		dict_set(dict, "b", "bar");
	}
	
	char *value = (char *)dict_get(dict, "a");

	pthread_exit(NULL);
}

// use the dict
void *use_dict2(void *arg) {
	DICT *dict = (DICT *)arg;

	int i;
	for (i = 0; i < NUM_TESTS; i++) {
		dict_set(dict, "a", "baz");
		dict_set(dict, "b", "jah");
		dict_clear(dict, "b");
	}
	char *value = (char *)dict_get(dict, "a");

	pthread_exit(NULL);
}

// use the dict
void *use_dict3(void *arg) {
	DICT *dict = (DICT *)arg;

	int i;
	for (i = 0; i < NUM_TESTS; i++) {
		dict_set(dict, "a", "ang");
		dict_set(dict, "b", "lee");
		dict_clear(dict, "a");
	}
	char *value = (char *)dict_get(dict, "a");

	pthread_exit(NULL);
}

// test the dict
int main(int argc, char *argv[]) {
	pthread_t p1, p2, p3;

	// create a dict
	DICT *dict = dict_create();

	// create some threads
	pthread_create(&p1, NULL, use_dict1, (void *)dict);
	pthread_create(&p2, NULL, use_dict2, (void *)dict);
	pthread_create(&p3, NULL, use_dict3, (void *)dict);

	// wait for threads to terminate
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);

	// print the keys in the dictionary
	dict_print_keys(dict);

	pthread_exit(NULL);
}

