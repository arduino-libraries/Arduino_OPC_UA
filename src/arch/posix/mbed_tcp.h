#pragma once

#include "../eventloop_posix.h"

#include "mbed.h"

int mbed_send(UA_FD fd, const void * data, size_t size, int ignored);
int mbed_recv(UA_FD fd, void * data, nsapi_size_t size, int ignored);
int mbed_close(UA_FD fd);
int mbed_connect(UA_FD fd, SocketAddress* addr);
int mbed_setsockopt(UA_FD fd, int level, int optname, const void *optval, unsigned optlen);
int mbed_getsockopt(UA_FD fd, int level, int optname, void *optval, unsigned *optlen);

TCPSocket * socket(int family, int type, int proto);
void freeaddrinfo(void * c);
