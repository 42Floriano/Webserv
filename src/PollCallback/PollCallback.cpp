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

#include <stdexcept>
#include <unistd.h>
#include <poll.h>
#include "PollCallback.hpp"
#include "PollSet.hpp"

PollCallback::PollCallback(PollSet &pset, int fd):
        pset(pset),
        fd(fd),
        is_closed(false)
{

};

PollCallback::~PollCallback()
{

}

void	PollCallback::unregister(void)
{
        this->pset.removeCallback(this);
}

void	PollCallback::on(short pollevent)
{
        switch (pollevent)
        {
        case POLLIN:
                this->_onPOLLIN();
                break;
        case POLLPRI:
                this->_onPOLLPRI();
                break;
        case POLLOUT:
                this->_onPOLLOUT();
                break;
        case POLLERR:
                this->_onPOLLERR();
                break;
        case POLLHUP:
                this->_onPOLLHUP();
                break;
        case POLLNVAL:
                this->_onPOLLNVAL();
                break;
        default:
                std::stringstream msg;
                msg << "Unhandled event (" << pollevent << ") on fd " << this->fd;
                throw std::runtime_error(msg.str());
                break;
        }
}

int	PollCallback::close()
{
        return ::close(this->fd);
};

static void throw_unhandeled_event(int fd, std::string event)
{
        std::stringstream errormsg;
        errormsg << "Unhandled " << event << " on fd " << fd;
        throw std::runtime_error(errormsg.str());
};

void	PollCallback::_onPOLLIN(void)
{
        throw_unhandeled_event(this->fd, "POLLIN");
};

void	PollCallback::_onPOLLPRI(void)
{
        throw_unhandeled_event(this->fd, "POLLPRI");
};

void	PollCallback::_onPOLLOUT(void)
{
        throw_unhandeled_event(this->fd, "POLLOUT");
};

void	PollCallback::_onPOLLRDHUP(void)
{
        throw_unhandeled_event(this->fd, "POLLRDHUP");
};

void	PollCallback::_onPOLLERR(void)
{
        throw_unhandeled_event(this->fd, "POLLERR");
};

void	PollCallback::_onPOLLHUP(void)
{
        throw_unhandeled_event(this->fd, "POLLHUP");
};

void	PollCallback::_onPOLLNVAL(void)
{
        throw_unhandeled_event(this->fd, "POLLNVAL");
};
