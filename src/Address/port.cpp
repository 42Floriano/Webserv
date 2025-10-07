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

#include "Address.hpp"

uint16_t	Address_storage::port(void) const
{

        uint16_t			port;
        struct sockaddr_in	*addr_v4;
        struct sockaddr_in6	*addr_v6;

        switch(this->family())
        {

        case AF_INET:
                addr_v4 = (struct sockaddr_in *)&this->_storage;
                port = ntohs(addr_v4->sin_port);
                break;
        case AF_INET6:
                addr_v6 = (struct sockaddr_in6 *)&this->_storage;
                port = ntohs(addr_v6->sin6_port);
                break;
        default:
                port = -1;
                break;
        }
        return port;
}

const std::string& Address_storage::portstr(void) const
{
        return (this->_portstr);
}
