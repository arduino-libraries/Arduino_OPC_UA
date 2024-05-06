/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2016-2017 (c) Julius Pfrommer, Fraunhofer IOSB
 *    Copyright 2017 (c) Stefan Profanter, fortiss GmbH
 */

#ifndef PLUGINS_ARCH_POSIX_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_POSIX_UA_ARCHITECTURE_H_

#include "../../open62541.h"

#ifdef UA_ARCHITECTURE_POSIX

_UA_BEGIN_DECLS

#define UA_IPV6 1
#define UA_SOCKET uintptr_t //(Socket*)
#define UA_INVALID_SOCKET -1
#define UA_ERRNO errno
#define UA_INTERRUPTED EINTR
#define UA_AGAIN EAGAIN /* the same as wouldblock on nearly every system */
#define UA_INPROGRESS EINPROGRESS
#define UA_WOULDBLOCK EWOULDBLOCK
#define UA_POLLIN POLLIN
#define UA_POLLOUT POLLOUT
#define UA_SHUT_RDWR 0

#define UA_poll poll
#define UA_send mbed_send
#define UA_recv mbed_recv
#define UA_close mbed_close
#define UA_connect mbed_connect
#define UA_getsockopt mbed_getsockopt
#define UA_setsockopt mbed_setsockopt
#define UA_accept mbed_accept
#define UA_listen mbed_listen
#define UA_getnameinfo mbed_getnameinfo
#define UA_getaddrinfo  mbed_addrinfo
#define UA_bind mbed_bind
#define UA_inet_pton inet_pton
#if UA_IPV6
# define UA_if_nametoindex if_nametoindex
#endif

#define UA_clean_errno(STR_FUN) (errno == 0 ? (char*) "None" : (STR_FUN)(errno))

#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { \
    char *errno_str = UA_clean_errno(strerror); \
    LOG; \
    errno = 0; \
}
#define UA_LOG_SOCKET_ERRNO_GAI_WRAP(LOG) { \
    const char *errno_str = UA_clean_errno(gai_strerror); \
    LOG; \
    errno = 0; \
}

_UA_END_DECLS

#endif /* UA_ARCHITECTURE_POSIX */

#endif /* PLUGINS_ARCH_POSIX_UA_ARCHITECTURE_H_ */
