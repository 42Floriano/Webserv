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

static void	acceptConnection(PollSock *self);
static void	handleIncomingData(PollSock *self);

void	PollSock::_onPOLLIN(void)
{
        if (this->state == Socket::listening)
                acceptConnection(this);
        else if (this->state == Socket::connected)
                handleIncomingData(this);
}

static void	acceptConnection(PollSock *self)
{
        int			client_fd;
        Address		*client_address;

        if (self->state != Socket::listening)
                throw std::runtime_error("Why are we accepting connections on a non-listening socket ???");
        try
        {
                self->accept(&client_fd, &client_address);
                self->onConnection(client_fd, client_address);
        }
        catch (int err)
        {
                (void) err;
        }
}

static void	handleIncomingData(PollSock *self)
{
        char	c = 0;
        ssize_t	retval;

        if (self->state != Socket::connected)
                throw std::runtime_error("Why are we handling incoming data on a non-connected socket ???");
        retval = ::recv(self->fd(), &c, 1, MSG_PEEK);
        if (retval == 0)
                self->onDisconnect();
        else if (retval == 1)
                self->onData();
        else
                self->onError();
}
