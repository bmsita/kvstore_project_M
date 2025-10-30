#include "client.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int send_command(const char *command) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
        die("socket");

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        die("connect");


    if (write(fd, command, strlen(command)) < 0)
        die("write");
    if (write(fd, "\n", 1) < 0)
        die("write newline");


    char buf[BUF_SIZE + 1];
    ssize_t n = read(fd, buf, BUF_SIZE);
    if (n < 0)
        die("read");
    buf[n] = '\0';

    printf("[client] Server reply: %s", buf);

    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"COMMAND\"\n", argv[0]);
        return 1;
    }

    return send_command(argv[1]);
}
