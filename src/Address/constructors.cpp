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

#include <cstring>
#include <sstream>
#include <sys/un.h>
#include "Address.hpp"

/* Init the static members */

Address::Address(std::string host, std::string port)
{

        this->configure(host, port);
        this->getaddrinfo();
}

/* rewrite this: rn repeats 2 many lines from fn above */
Address::Address(std::string host, uint16_t port)
{

        this->configure(host, port);
        this->getaddrinfo();
}

Address::Address(uint32_t host, uint16_t port)
{

        struct sockaddr_in	*thisaddr = (struct sockaddr_in *)this->storage_ptr();
        thisaddr->sin_family = AF_INET;
        thisaddr->sin_addr.s_addr = htonl(host);
        thisaddr->sin_port = htons(port);
        this->setStorageSize(sizeof(struct sockaddr_in));

        /* TODO: populate this->_hoststr (string) */
        /* TODO: populate this->_portstr (string) */
        const std::string flemme = "too lazy to parse it (but data is there)";
        this->configure(flemme, flemme);
}

Address::Address(std::string path)
{

        struct sockaddr_un	*thisaddr = (struct sockaddr_un *)this->storage_ptr();
        thisaddr->sun_family = AF_UNIX;
        ::strncpy(thisaddr->sun_path, path.c_str(), path.size());
        thisaddr->sun_path[path.size()] = 0;
        this->setStorageSize(path.size() + sizeof(AF_UNIX));
}

Address::Address(struct sockaddr *addr, socklen_t addrlen)
{
        memset(this->storage_ptr(), 0, sizeof(struct sockaddr_storage));
        memcpy(this->storage_ptr(), addr, addrlen);
        this->setStorageSize(addrlen);
}
