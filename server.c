#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/kvstore.sock"
#define BUF_SIZE 1024

int main() {
    
    void *handle = dlopen("./libkvstore.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Failed to load library: %s\n", dlerror());
        exit(1);
    }

    
    const char *(*set_value)(const char *, const char *) = dlsym(handle, "set_value");
    const char *(*get_value)(const char *) = dlsym(handle, "get_value");

    if (!set_value || !get_value) {
        fprintf(stderr, "Error loading symbols: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }


    int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(listen_fd, 5);
    printf("[server] Listening on %s\n", SOCKET_PATH);

    for (;;) {
        int client_fd = accept(listen_fd, NULL, NULL);
        if (client_fd < 0) continue;

        char buf[BUF_SIZE];
        read(client_fd, buf, sizeof(buf));
        buf[strcspn(buf, "\n")] = '\0';

        char cmd[16], key[64], value[256];
        int n = sscanf(buf, "%15s %63s %255[^\n]", cmd, key, value);
        char reply[256];

        if (n >= 2 && strcasecmp(cmd, "SET") == 0)
            snprintf(reply, sizeof(reply), "%s", set_value(key, value));
        else if (n >= 2 && strcasecmp(cmd, "GET") == 0)
            snprintf(reply, sizeof(reply), "%s\n", get_value(key));
        else
            snprintf(reply, sizeof(reply), "ERROR: Invalid command\n");

        write(client_fd, reply, strlen(reply));
        close(client_fd);
    }

    dlclose(handle);
    return 0;
}
