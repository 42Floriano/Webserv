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
#include "Console.hpp"

void	HttpHeaders::insert(const std::string &k, const std::string &value)
{
        std::string key = k;
        HttpHeaders::normalize_key(key);
        std::pair<std::map<std::string, std::string>::iterator, bool> res =
                this->map::insert(std::pair<std::string, std::string>(key, value));
        if (res.second == false)
                console::error << "map insertion (" + key  + ", " + value + ") failed" << std::endl;
}
