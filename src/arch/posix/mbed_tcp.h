#pragma once

#include "../eventloop_posix.h"

#include "mbed.h"

#define socklen_t       size_t

struct sockaddr {
    SocketAddress ai;
};

struct sockaddr_storage {
    SocketAddress ai;
};

struct addrinfo {
    SocketAddress ai;
    int     ai_flags;
    int     ai_family;
    int     ai_socktype;
    int     ai_protocol;
    size_t  ai_addrlen;
    struct  sockaddr *ai_addr;
    char    *ai_canonname;     /* canonical name */
    struct  addrinfo *ai_next; /* this struct can form a linked list */
};

extern "C"
{
    int mbed_send(UA_FD fd, const void * data, size_t size, int ignored);
    int mbed_recv(UA_FD fd, void * data, nsapi_size_t size, int ignored);
    int mbed_close(UA_FD fd);
    int mbed_connect(UA_FD fd, struct sockaddr* addr);
    int mbed_setsockopt(UA_FD fd, int level, int optname, const void *optval, unsigned optlen);
    int mbed_getsockopt(UA_FD fd, int level, int optname, void *optval, unsigned *optlen);
    UA_SOCKET mbed_accept(UA_FD fd, struct sockaddr* s, size_t* s_sz);
    int mbed_bind(UA_FD fd, struct sockaddr* addr, size_t s_sz);
    int mbed_getnameinfo(struct sockaddr* sa, size_t sa_sz, char* hoststr, size_t host_sz, struct sockaddr*, uint8_t, uint8_t);
    int mbed_listen(UA_FD fd, int ignored);
    int mbed_addrinfo(const char* hostname, const char* portstr, struct addrinfo* hints, struct addrinfo** info);

    UA_SOCKET socket(int family, int type, int proto);
    void freeaddrinfo(void * c);
    int gethostname(char *str, size_t len);

    inline char* gai_strerror(int err) {
        char str[8];
        return itoa(err, str, 10);
    }
    inline void shutdown(UA_SOCKET s, uint8_t flag)
    {
      /* There is nothing to do here.
       *
       * When an incoming connection is accepted by TCPSocket::accept()
       * a new TCPSocket is generated and allocated on the heap. At the
       * same time a TCPSocket internal flag called "_factory_allocated"
       * is set which causes the dynamically allocated memory to be
       * deallocated when calling TCPSocket::close().
       *
       * As a consequence there is no need to deallocate or close any
       * TCPSocket object in here, as this is done when calling UA_close
       * (= mbed_close). Calling close already here would cause a crash
       * as the object would have been deallocated by the time the
       * OPCUA stack would invoke UA_close.
       */
    }
}

#define IPPROTO_TCP     0
#define IPPROTO_UDP     1
#define TCP_NODELAY     0
#define SOL_SOCKET      NSAPI_SOCKET
#define SO_REUSEPORT    0
#define SO_REUSEADDR    NSAPI_REUSEADDR
#define SO_ERROR        0
#define NI_NUMERICHOST  0
#define NI_NUMERICHOST  0
#define AF_INET6        6
#define IPPROTO_IPV6    6
#define IPV6_V6ONLY     6
#define AF_UNSPEC       5
#define SOCK_STREAM     8
#define AI_PASSIVE      2
