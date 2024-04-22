typedef struct cache {
  int* accessed;
  int size;
  int* addr;
  float* data;
} CACHE;
   
CACHE *cache_new(int size);
float  cache_lookup(CACHE *cache, int i);
void   cache_insert(CACHE *cache, int i, float x);
void   cache_clear(CACHE *cache, int i);
