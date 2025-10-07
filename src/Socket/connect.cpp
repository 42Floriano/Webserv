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

#include <cerrno>
#include "Console.hpp"
#include "Socket.hpp"

void	Socket::connect(const std::string &host, const std::string &service)
{

        this->remoteAddress = new Address(host, service);

        errno = 0;
        int	retval = ::connect(
                              this->fd,
                              this->remoteAddress->ptr(),
                              this->remoteAddress->len()
                      );
        if (retval == -1)
                throw errno;

        this->state = xsocket::connected;
}

bool	Socket::isConnected(int fd)
{
        ssize_t	readlen;
        char	c;

        c = 0;

        // Peek the
        try
        {
                readlen = ::recv(fd, &c, 1, MSG_PEEK | MSG_DONTWAIT);
        }
        catch (int error)
        {
                if (error != EAGAIN)
                        throw ;
                return (true);
        }

        if (readlen == 1)
        {
                console::debug << "Peeked: " << c << std::endl;
        }

        return readlen == 1 ? true : false;

}
