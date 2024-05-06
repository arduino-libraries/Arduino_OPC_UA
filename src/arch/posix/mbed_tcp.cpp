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

  if (rc == NSAPI_ERROR_OK) {
    printf("mbed_recv: rc = NSAPI_ERROR_OK");
  }
  else if (rc > 0) {
    printf("mbed_recv: got %d on %x, data: %x, size: %d\n", rc, fd, (uint32_t)data, size);
  }
  else {
    printf("mbed_recv error: rc = %d", rc);
  }

  return rc;
}

int mbed_close(UA_FD fd)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->close();
  return rc;
}

int mbed_connect(UA_FD fd, SocketAddress* addr)
{
  TCPSocket * sock = (TCPSocket *)fd;
  nsapi_error_t const rc = sock->connect(*addr);
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

TCPSocket * socket(int /* family */, int /* type */, int /* proto */)
{
  TCPSocket * tcp_socket = new TCPSocket();
  tcp_socket->sigio(mbed::callback(event, tcp_socket));
  tcp_socket->open(NetworkInterface::get_default_instance());
  return tcp_socket;
}

void freeaddrinfo(void * /* c */)
{
  /* Not implemented. */
}
