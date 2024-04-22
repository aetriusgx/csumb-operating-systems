#define MAX_ITEMS 500

typedef struct {
    // sync. variables
    pthread_mutex_t lock;
    // state variables
    char *keys[MAX_ITEMS];
    void *values[MAX_ITEMS];
} DICT;

DICT *dict_create();
void dict_clear(DICT *dict, char *key);
void dict_set(DICT *dict, char *key, void *value);
void *dict_get(DICT *dict, char *key);
void dict_print_keys(DICT *dict);
