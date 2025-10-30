#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    void (*set_value)(const char *, const char *);
    const char* (*get_value)(const char *);
    char *error;

    handle = dlopen("./libkvstore.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    dlerror();


    *(void **)(&set_value) = dlsym(handle, "set_value");
    *(void **)(&get_value) = dlsym(handle, "get_value");

    
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error loading symbols: %s\n", error);
        dlclose(handle);
        return 1;
    }


    set_value("name", "Rojalin");
    printf("Value: %s\n", get_value("name"));


    dlclose(handle);
    return 0;
}
