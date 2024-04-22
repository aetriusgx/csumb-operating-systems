
/* 
 * A dictionary that maps from strings to pointers
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dict.h"

DICT *dict_create() {
    DICT *dict;
    dict = malloc(sizeof(DICT));
    assert(dict != NULL);

    // initialize lock
    pthread_mutex_init(&dict->lock, NULL);

    // initialize data
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        dict->keys[i] = NULL;
        dict->values[i] = NULL;
    }
    return(dict);
}

// set or update item with given key; value must not be NULL
void dict_set(DICT *dict, char *key, void *value) {
	if (value == NULL) {
		printf("error: cannot set a dict entry to NULL\n");
		exit(EXIT_FAILURE);
	}
    int i;
	
	// if key in dict, update its value
	pthread_mutex_lock(&dict->lock);
	for (i = 0; i < MAX_ITEMS; i++) {
		if (dict->keys[i] == key) {
			dict->values[i] = value;
			pthread_mutex_unlock(&dict->lock);
			return;
		}
	}

	// key not in dict, so set the value
	for (i = 0; i < MAX_ITEMS; i++) {
		if (dict->keys[i] == NULL) {
			dict->keys[i] = key;
			dict->values[i] = value;
			pthread_mutex_unlock(&dict->lock);
			return;
		}
	}
	printf("error: dictionary is full\n");
	pthread_mutex_unlock(&dict->lock);
	exit(EXIT_FAILURE);
}

// return the item with the given key, or NULL if no item has the key
void *dict_get(DICT *dict, char *key) {
	pthread_mutex_lock(&dict->lock);
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        if (dict->keys[i] != NULL && strcmp(dict->keys[i], key) == 0) {
			pthread_mutex_unlock(&dict->lock);
            return dict->values[i];
        }
    }
	pthread_mutex_unlock(&dict->lock);
    return NULL;
}

// clear the key from the store, or do nothing if the key not present
void dict_clear(DICT *dict, char *key) {

	// to clear the key from the store, set the value associated
	// with the key to NULL
	pthread_mutex_lock(&dict->lock);
	for (int i = 0; i < MAX_ITEMS; i++) {
		if (dict->keys[i] == key) {
			dict->values[i] = NULL;
			pthread_mutex_unlock(&dict->lock);
			return;
		}
	}

	pthread_mutex_unlock(&dict->lock);
	return;
}

// print the keys in the dict
void dict_print_keys(DICT *dict) {
	pthread_mutex_lock(&dict->lock);
    int i;
	printf("keys:\n");
    for (i = 0; i < MAX_ITEMS; i++) {
        if (dict->keys[i] != NULL) {
			printf("%s \n", dict->keys[i]);
        }
    }
	pthread_mutex_unlock(&dict->lock);
}
