#include "mbed_tcp.h"

#include "PortentaEthernet.h"

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
  nsapi_error_t rc = sock->getsockopt(level, optname, optval, optlen);
  if (rc == NSAPI_ERROR_UNSUPPORTED) {
      rc = 0;
  }
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
    memset(name, 0, host_sz);
    memcpy(name, ((SocketAddress*)fd)->get_ip_address(), strlen(((SocketAddress*)fd)->get_ip_address()));
    return 0;
}

int mbed_addrinfo(const char* hostname, const char* portstr, struct addrinfo* hints, struct addrinfo** info)
{
  if (hostname == NULL)
  {
    static const char * localhost = "localhost";
    hostname = localhost;
  }

  SocketAddress mbed_hints(hostname, atoi(portstr));
  mbed_hints.set_ip_address(Ethernet.localIP().toString().c_str());
  SocketAddress * mbed_res;

//  /* rc either holds the number of results uncovered or a negative error code. */
//  auto rc = NetworkInterface::get_default_instance()->getaddrinfo(hostname, &mbed_hints, &mbed_res);
//  if (rc < 0)
//  {
//    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "NetworkInterface::get_default_instance()->getaddrinfo(...) failed with %d", rc);
//    return UA_STATUSCODE_BAD;
//  }
//
//  int const addr_cnt = rc;
//  if (addr_cnt == 0)
//  {
//    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "NetworkInterface::get_default_instance()->getaddrinfo(...) found no addresses");
//    return UA_STATUSCODE_BAD;
//  }

  /* Note: we currently support only a single address result. */
  static struct sockaddr ai_addr;
  //ai_addr.ai = mbed_res[0];
  ai_addr.ai = mbed_hints;

  static struct addrinfo res;
  memcpy(&res, hints, sizeof(struct addrinfo));

  res.ai_addr = &ai_addr;
  res.ai_next = NULL;
  info[0] = &res;

  return UA_STATUSCODE_GOOD;
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
