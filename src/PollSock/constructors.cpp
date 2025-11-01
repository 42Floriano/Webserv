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

#include "PollSock.hpp"
#include <unistd.h>

PollSock::PollSock(PollSet &pset, int domain, int type, int protocol):
        Socket(domain, type, protocol),
        PollCallback(pset, this->Socket::fd),
        _reserved_fd(-1)
{
};

PollSock::PollSock(PollSet &pset, int fd, Address *addr):
        Socket(fd, addr),
        PollCallback(pset, fd),
        _reserved_fd(-1)
{
};

PollSock::~PollSock(void)
{
        console::debug << "Deconstructing Socket (fd " << this->fd() << ")" <<
                       std::endl;
        try
        {
                this->pset.removeCallback(POLLIN, this);
                this->pset.removeCallback(POLLOUT, this);
                this->pset.removeCallback(POLLHUP, this);
                this->pset.removeCallback(POLLERR, this);
        }
        catch (const std::exception &err)
        {
                (void) err;
        }
        ::close(this->_reserved_fd);
        ::close(this->fd());
}
