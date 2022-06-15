#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int tcp_bind(int listen_fd, short port);
void SEND_FILE(int accept_fd, char *path);