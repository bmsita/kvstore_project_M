#ifndef KVSTORE_H
#define KVSTORE_H

#define MAX_PAIRS 100

struct kv_pair {
    char key[64];
    char value[256];
};

const char *set_value(const char *key, const char *value);
const char *get_value(const char *key);
void clear_store(void);

#endif
