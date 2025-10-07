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

#include <poll.h>
#include "xpollfd.hpp"

xpollfd::xpollfd(void)
{
        this->fd = -1;
        this->events = 0;
        this->revents = 0;
};

xpollfd::xpollfd(int fd, short events)
{
        this->fd = fd;
        this->events = events;
        this->revents = 0;
};

bool	xpollfd::operator==(const xpollfd &rhs) const
{
        return rhs.fd == this->fd;
};

xpollfd&	xpollfd::operator=(const pollfd &pfd)
{
        this->fd = pfd.fd;
        this->events = pfd.events;
        this->revents = pfd.revents;
        return (*this);
};

void	xpollfd::listen(short event)
{
        this->events |= event;
};

void	xpollfd::unlisten_to(short event)
{
        this->events &= ~event;
};

void	xpollfd::listen_all()
{
        this->events = POLLIN | POLLOUT | POLLHUP | POLLERR;
};

void	xpollfd::unlisten_all()
{
        this->events = 0;
};

pollfd&	xpollfd::unwrap(void)
{
        return *((pollfd *)this);
};
