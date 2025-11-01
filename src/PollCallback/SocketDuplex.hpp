#ifndef SOCKETDUPLEX_HPP
# define SOCKETDUPLEX_HPP

#include "Address.hpp"
#include <streambuf>
#include "Socket.hpp"
#include "PollSet.hpp"
#include "FdDuplex.hpp"

struct SocketDuplex: private Socket, public FdDuplex
{
        SocketDuplex(PollSet &pset, int fd, Address *addr, std::streambuf *in,
                     std::streambuf *out);
        ssize_t	_write(char *buf, size_t);
        ssize_t	_read(char *buf, size_t);
};

#endif
