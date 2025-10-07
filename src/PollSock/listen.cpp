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
#include "PollSock.hpp"

void PollSock::listen(
        const std::string &host,
        const std::string &port,
        int backlog
)
{
        this->bind(host, port);
        this->listen(backlog);
}

void PollSock::listen(int backlog)
{
        this->_reserved_fd = ::dup(this->fd());
        this->Socket::listen(backlog);
        this->_pset.registerCallback(POLLIN, this);
}
