#include "mbed_tcp.h"

int mbed_send(UA_FD fd, const void * data, size_t size, int ignored)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_value_or_error_t const rc = sock->send(data, static_cast<nsapi_size_t>(size));
  return rc;
}

int mbed_recv(UA_FD fd, void * data, nsapi_size_t size, int ignored)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_value_or_error_t const rc = sock->recv(data, size);

  if (rc == 0) {
    UA_ERRNO = UA_WOULDBLOCK;
  }

  return rc;
}

int mbed_close(UA_FD fd)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->close();
  return rc;
}

int mbed_connect(UA_FD fd, struct sockaddr* addr)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->connect(*((SocketAddress*)addr));
  return rc;
}

int mbed_setsockopt(UA_FD fd, int level, int optname, const void *optval, unsigned optlen)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->setsockopt(level, optname, optval, optlen);
  return rc;
}

int mbed_getsockopt(UA_FD fd, int level, int optname, void *optval, unsigned *optlen)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->getsockopt(level, optname, optval, optlen);
  return rc;
}

extern rtos::EventFlags _events;
void event(Socket * s)
{
  _events.set((uint32_t)s);
  //printf("Processing event: %x\n", (uint32_t)s);
}

UA_SOCKET mbed_accept(UA_FD fd, struct sockaddr* s, size_t* s_sz) {
    // TODO: do something to retrieve s (getpeername?)
    nsapi_error_t error;
    TCPSocket* sock = ((TCPSocket*)fd)->accept(&error);
    if (sock && error == NSAPI_ERROR_OK) {
        sock->sigio(mbed::callback(event, sock));
        sock->getpeername((SocketAddress*)s);
        sock->set_timeout(1500);
        sock->set_blocking(false);
    } else {
        errno = UA_INTERRUPTED;
    }
    return (UA_SOCKET)sock;
}

int mbed_bind(UA_FD fd, struct sockaddr* addr, size_t s_sz) {
    return ((TCPSocket*)fd)->bind(((SocketAddress*)addr)->get_port());
}

int mbed_getnameinfo(struct sockaddr* fd, size_t sa_sz, char* name, size_t host_sz, struct sockaddr*, uint8_t, uint8_t) {
    memcpy(name, ((SocketAddress*)fd)->get_ip_address(), strlen(((SocketAddress*)fd)->get_ip_address()));
    return 0;
}

int mbed_addrinfo(const char* hostname, const char* portstr, struct addrinfo* hints, struct addrinfo** info) {
    auto ret = NetworkInterface::get_default_instance()->getaddrinfo(hostname, (SocketAddress*)&hints, (SocketAddress**)&info);
    hints->ai_addr = (struct  sockaddr*)hints;
    (*info)->ai_addr = (struct  sockaddr*)info;
    return ret;
}

int mbed_listen(UA_FD fd, int ignored) {
    ((TCPSocket*)fd)->set_blocking(false);
    return ((TCPSocket*)fd)->listen(1);
}

UA_SOCKET socket(int /* family */, int /* type */, int proto)
{
  if (proto == IPPROTO_TCP) {
    TCPSocket * _socket = new TCPSocket();
    _socket->sigio(mbed::callback(event, _socket));
    _socket->open(NetworkInterface::get_default_instance());
    return (UA_SOCKET)_socket;
  }
  if (proto == IPPROTO_UDP) {
    UDPSocket * _socket = new UDPSocket();
    _socket->sigio(mbed::callback(event, _socket));
    _socket->open(NetworkInterface::get_default_instance());
    return (UA_SOCKET)_socket;
  }
}

void freeaddrinfo(void * /* c */)
{
  /* Not implemented. */
}
