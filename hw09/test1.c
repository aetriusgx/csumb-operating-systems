/* 
 * Test the dict class
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

int main(int argc, char *argv[]) {

	// create a dict
	DICT *dict = dict_create();

	// use it
	dict_set(dict, "a", "foo");
	dict_set(dict, "b", "bar");
	char *value = (char *)dict_get(dict, "a");
	if (strcmp(value, "foo") != 0) {
		exit(EXIT_FAILURE);
	} 
	return 0;
}

