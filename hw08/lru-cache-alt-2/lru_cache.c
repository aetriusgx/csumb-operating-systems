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
  cache->addr = malloc(size * sizeof(int));
  cache->data = malloc(size * sizeof(float));
  cache->size = size;
}

// is the cache contains an element with key value i, return its value,
// else return -1
float cache_lookup(CACHE* cache, int i) {
  int j;
  float data;
  for (j = 0; j < cache->size; j++) {
    if (cache->addr[j] == i) {
      data = cache->data[j];
      // Shift stuff to the left
      for (int k = j; k < cache->size-1; k++) {
        cache->addr[k] = cache->addr[k+1];
        cache->data[k] = cache->data[k+1];
      }
      
      cache->addr[cache->size-1] = i;
      cache->data[cache->size-1] = data;
      return cache->data[cache->size-1];
    }
  }

  return -1.0;
}

// record in the cache that the data element with key i has value x
// LRU replacement policy is used
void cache_insert(CACHE* cache, int i, float x) {
  for (int j = cache->size-1; j > 0; j--) {
    if (cache->addr[j] == -1) {
      cache->addr[j] = i;
      cache->data[j] = x;
      return;
    }
  }
  
  for (int j = 0; j < cache->size; j++) {
      cache->addr[j] = cache->addr[j+1];
      cache->data[j] = cache->data[j+1];
  }

  cache->addr[cache->size-1] = i;
  cache->data[cache->size-1] = x;
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

