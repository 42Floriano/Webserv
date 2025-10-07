/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "xsocket.hpp"

class Socket: public xsocket
{
public:
        const static int DEFAULT_BACKLOG = 4096;

        Socket(int domain, int type, int protocol);
        Socket(int fd, Address *addr);
        ~Socket(void);

        void		bind(const std::string &addr, const std::string &service);
        void		listen(int backlog = Socket::DEFAULT_BACKLOG);
        void		listen(const std::string &addr, const std::string &port);
        void		accept(int *client_fd, Address **addr);
        void		connect(const std::string &addr, const std::string &service);
        ssize_t		read(char *buf, size_t size);
        ssize_t		write(const char *buf, size_t size);
        void		close(void);

public:
        static bool isConnected(int fd);
};

#endif
