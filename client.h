#ifndef CLIENT_H
#define CLIENT_H

#define SOCKET_PATH "/tmp/kvstore.sock"
#define BUF_SIZE 1024

int send_command(const char *command);

#endif
