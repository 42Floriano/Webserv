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
#include <poll.h>
#include "PollCallback.hpp"

/* Public Methods */

PollCallback::~PollCallback()
{
        // does nothing (is pure)
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
        // case POLLRDHUP:
        // 	this->_onPOLLRDHUP();
        // 	break;
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
                break;
        }

}

int	PollCallback::fd() const
{
        return (-1);
}

void	PollCallback::_onPOLLIN(void)
{
        //base class does nothing
};

void	PollCallback::_onPOLLPRI(void)
{
        //base class does nothing
};

void	PollCallback::_onPOLLOUT(void)
{
        //base class does nothing
};

//#include <iostream>

void	PollCallback::_onPOLLRDHUP(void)
{
        //base class does nothing
};

void	PollCallback::_onPOLLERR(void)
{
        //base class does nothing
}

void	PollCallback::_onPOLLHUP(void)
{
        //base class does nothing
}

void	PollCallback::_onPOLLNVAL(void)
{
        //base class does nothing
}
