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
  cache->size = size;
}

// is the cache contains an element with key value i, return its value,
// else return -1
float cache_lookup(CACHE* cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
    if (cache->addr[j] == i) {
      cache->accessed[j]++;
      // Should reorganize so that last element is the one least used
      // If a segment >1 have 0 accesses, new element should be moved *in front* of those
      // This allows the last element to be the element least accessed
      //    and is the element not used recently
      
      // Put current element into temp vars
      // Shift data over, up to point of element index
      // Place current data into new index, now duped
      int accessed = cache->accessed[j];
      int addr = cache->addr[j];
      float data = cache->data[j];
      for (int k = 0; k < j - 1; k++) {
        // if k access lte j access
        if (cache->accessed[k] <= cache->accessed[j]) {
          // Shift data over
          for (int m = k+1; m < j; m++) {
            cache->addr[m] = cache->addr[k];
            cache->accessed[m] = cache->accessed[k];
            cache->data[m] = cache->data[k];
          }
          // Replace k point with temp data
          cache->addr[k] = addr;
          cache->accessed[k] = accessed;
          cache->data[k] = data;
          return cache->data[k];
        }
      }

      return cache->data[j];
    }
  }

  return -1.0;
}

// record in the cache that the data element with key i has value x
// LRU replacement policy is used
void cache_insert(CACHE* cache, int i, float x) {
  if (cache->data[cache->size - 1] == -1) {
    // If the end is empty, we are safe to add a new thing to the end
    int j;
    for (j = 0; j < cache->size; j++) {
      // Insert past used space
      if (cache->addr[j] == -1) {
        cache->accessed[j] = 0;
        cache->addr[j] = i;
        cache->data[j] = x;
        return;
      }
    }
  }
  // If the data set is full, the end should contain least accessed element
  // Least recently used should be the one overwritten
  cache->accessed[cache->size-1] = 0;
  cache->addr[cache->size-1] = i;
  cache->data[cache->size-1] = x;
}

// remove cache element having key value i, if such an element exists
void cache_clear(CACHE* cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
     if (cache->addr[j] == i) {
        cache->accessed[j] = 0;
        cache->addr[j] = -1;
        break;
     }
  }
}

