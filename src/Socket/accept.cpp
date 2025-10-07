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

#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <Console.hpp>
#include "Socket.hpp"

void	Socket::accept(int *client_fd, Address **client_address)
{

        struct sockaddr_storage storage;
        socklen_t				size;

        memset(&storage, 0, sizeof(sockaddr_storage));
        size = 0;

        errno = 0;
        *client_fd = ::accept(this->fd, (struct sockaddr *)&storage, &size);
        if (*client_fd < 0 && errno != EMFILE)
        {
                int		err = errno;
                throw err;
        }

        if (client_address)
        {
                *client_address = *client_fd > -1 ?
                                  new Address((struct sockaddr *)&storage, size):
                                  NULL;
        }

}
