#include <stdlib.h>
#include "lru_cache.h"

//
// Your implementations of cache_new, cache_lookup, cache_insert,
// and cache_clear go in this file.  You must use a least-recently-used
// cache replacement policy.
//

// return a new cache object
CACHE* cache_new(int size) {
  CACHE* cache = malloc(sizeof(CACHE));
  cache->accessed = malloc(size * sizeof(int));
  cache->addr = malloc(size * sizeof(int));
  cache->data = malloc(size * sizeof(float));
  cache->timer = 0;
  cache->size = size;
}

// is the cache contains an element with key value i, return its value,
// else return -1
float cache_lookup(CACHE* cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
    if (cache->addr[j] == i) {
      // Accessed value equal to increment of timer
      cache->accessed[j] = ++cache->timer;
      return cache->data[j];
    }
  }

  return -1.0;
}

// record in the cache that the data element with key i has value x
// LRU replacement policy is used
void cache_insert(CACHE* cache, int i, float x) {
  int j;
  // If the end is empty, we are safe to add a new thing to the end
  for (j = 0; j < cache->size; j++) {
    // Insert past used space
    if (cache->addr[j] == -1) {
      // Accessed value equal to timer, then increment
      cache->accessed[j] = cache->timer++;
      cache->addr[j] = i;
      cache->data[j] = x;
      return;
    }
  }

  // If the data set is full, use LRU policy
  // Find index with lowest time value
  // Preset to first element
  int min_index = 0;
  int min_time = cache->accessed[min_index];
  for (j = 0; j < cache->size; j++) {
    if (cache->accessed[j] < min_time) {
      min_index = j;
    }
  }
  // Replace min_index
  cache->addr[min_index] = i;
  cache->data[min_index] = x;
  cache->accessed[min_index] = cache->timer++;
  return;
}

// remove cache element having key value i, if such an element exists
void cache_clear(CACHE* cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
    if (cache->addr[j] == i) {
      cache->addr[j] = -1;
      break;
    }
  }
}

