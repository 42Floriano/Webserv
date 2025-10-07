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

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include "Console.hpp"
#include "Socket.hpp"

void	Socket::close(void)
{
        console::debug << "Closing (socket) fd " << this->fd << std::endl;

        if (this->address)
                delete (this->address);
        if (this->remoteAddress)
                delete (this->remoteAddress);

        errno = 0;
        ::close(this->fd);
        if (errno)
        {
                console::error << "Socket::close: " << strerror(errno) << std::endl;
        }
}
