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

#include "HttpHeaders.hpp"

void	HttpHeaders::remove(const std::string &header_name)
{
        std::string key = header_name;
        HttpHeaders::normalize_key(key);
        if (this->count(key) == 1)
        {
                // TODO: this->erase ...
        }
        else
        {
                // TODO: choose what to do when, key does not exist
        }
}
