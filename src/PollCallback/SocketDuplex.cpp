#include "SocketDuplex.hpp"

SocketDuplex::SocketDuplex(PollSet &pset, int fd, Address *addr,
                           std::streambuf *in, std::streambuf *out):
        Socket(fd, addr),
        FdDuplex(pset, this->Socket::fd, in, out)
{
};

ssize_t SocketDuplex::_read(char *buf, size_t buflen)
{
        return this->Socket::read(buf, buflen);
};

ssize_t SocketDuplex::_write(char *buf, size_t buflen)
{
        return this->Socket::write(buf, buflen);
};
