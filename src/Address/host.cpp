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

#include <sys/un.h>
#include "Address.hpp"

uint32_t	Address_storage::host(void) const
{

        uint32_t			host;
        struct sockaddr_in	*addr_v4;
        addr_v4 = (struct sockaddr_in *)&this->_storage;

        if (addr_v4->sin_family == AF_INET)
                host = ntohl(addr_v4->sin_addr.s_addr);
        else
                host = -1;
        return host;
}

const std::string& Address_storage::hoststr(void) const
{
        return (this->_hoststr);
}

char	*Address_storage::path(void) const
{
        struct sockaddr_un	*ptr;

        ptr = (struct sockaddr_un*)this->ptr();
        return (ptr->sun_path);
}
