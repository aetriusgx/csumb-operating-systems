
# the include file in cache_sim.c must be set to select cache implementation

rand:	cache_sim_rand
	./cache_sim_rand

cache_sim_rand: cache_sim.c random_cache.c
	sed 's/\#include.*cache\.h/\#include \"random_cache\.h/' cache_sim.c > temp.c
	gcc -o cache_sim_rand temp.c random_cache.c

clean:
	rm -f cache_sim_lru cache_sim_rand temp.c test[1-5] *~ 

