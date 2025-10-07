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

#include <sstream>
#include "Address_storage.hpp"

void	Address_storage::configure(const std::string &host,
                                 const std::string &port)
{
        this->_hoststr = host;
        this->_portstr = port;
}

void	Address_storage::configure(const std::string &host, u_int16_t port)
{
        std::stringstream	portstr;
        portstr << port;
        this->configure(host, portstr.str());

}

void	Address_storage::setStorageSize(socklen_t size)
{
        this->_storage_size = size;
}
