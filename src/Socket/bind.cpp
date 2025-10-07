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
#include "Socket.hpp"

void	Socket::bind(const std::string &addr, const std::string &service)
{

        // Allows the socket to bind to a previosuly used address
        int	opt = 1;
        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        // Constructs the address field
        this->address = new Address(addr, service);

        // Binds the socket to the address
        errno = 0;
        if(::bind(this->fd, this->address->ptr(), this->address->len()) < 0)
        {
                delete this->address;
                throw errno;
        }

        // Sets the inner state of the socket
        this->state = xsocket::bound;
}
