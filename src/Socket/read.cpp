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

#include <unistd.h>
#include <cerrno>
#include "Console.hpp"
#include "Socket.hpp"

ssize_t	Socket::read(char *buf, size_t len)
{

        /* Subject forbids to check the error number after a read */
        //errno = 0;
        ssize_t retval = ::recv(this->fd, buf, len, this->rflags);
        //if (retval < 0)
        //	throw errno;

        return (retval);
}
