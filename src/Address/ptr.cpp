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

struct sockaddr	*Address_storage::ptr(void) const
{
        struct sockaddr	*addr;

        addr = (struct sockaddr *)& this->_storage;
        return (addr);
}

struct sockaddr_storage	*Address_storage::storage_ptr(void) const
{
        struct sockaddr_storage	*addr;

        addr = (struct sockaddr_storage *)& this->_storage;
        return (addr);
}
