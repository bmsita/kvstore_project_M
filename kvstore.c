#include <string.h>
#include "kvstore.h"

static struct kv_pair store[MAX_PAIRS];
static int store_count = 0;

static int find_key(const char *key) {
    for (int i = 0; i < store_count; i++) {
        if (strcmp(store[i].key, key) == 0)
            return i;
    }
    return -1;
}

const char *set_value(const char *key, const char *value) {
    int idx = find_key(key);
    if (idx >= 0) {
        strncpy(store[idx].value, value, sizeof(store[idx].value) - 1);
    } else if (store_count < MAX_PAIRS) {
        strncpy(store[store_count].key, key, sizeof(store[store_count].key) - 1);
        strncpy(store[store_count].value, value, sizeof(store[store_count].value) - 1);
        store_count++;
    } else {
        return "ERROR: Store full\n";
    }
    return "OK\n";
}

const char *get_value(const char *key) {
    int idx = find_key(key);
    if (idx >= 0)
        return store[idx].value;
    return "NOT FOUND\n";
}

void clear_store(void) {
    store_count = 0;
}
