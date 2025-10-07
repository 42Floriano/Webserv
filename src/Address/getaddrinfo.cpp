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
#include <cstring>
#include <iostream>

void	Address_storage::getaddrinfo(void)
{
        int				error;
        struct addrinfo	hints;
        struct addrinfo	*infolist;

        ::memset(&hints, 0, sizeof(hints));
        error = ::getaddrinfo(this->_hoststr.c_str(), this->_portstr.c_str(), &hints,
                              &infolist);
        if (error)
        {
                std::cerr << "getaddrinfo: " << gai_strerror(error) << std::endl;
        }
        else
        {
                ::memcpy(&(this->_storage), infolist->ai_addr, infolist->ai_addrlen);
                this->_storage_size = infolist->ai_addrlen;
                freeaddrinfo(infolist);
        }
}
