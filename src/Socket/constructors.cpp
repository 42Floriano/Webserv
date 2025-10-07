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

#include "Socket.hpp"

Socket::Socket(int domain, int type, int protocol)
{
        this->state = xsocket::off;
        this->address = NULL;
        this->remoteAddress = NULL;
        this->domain = domain;
        this->type = type;
        this->protocol = protocol;
        this->rflags = MSG_DONTWAIT;
        this->wflags = MSG_DONTWAIT;
        this->fd = ::socket(domain, type, protocol);
};

Socket::Socket(int fd, Address *addr)
{
        this->state = xsocket::off;
        this->address = addr;
        this->remoteAddress = NULL;
        this->fd = fd;
        this->rflags = MSG_DONTWAIT;
        this->wflags = MSG_DONTWAIT;
};

Socket::~Socket(void)
{
        if (this->address)
                delete this->address;
        if (this->remoteAddress)
                delete this->remoteAddress;
}
