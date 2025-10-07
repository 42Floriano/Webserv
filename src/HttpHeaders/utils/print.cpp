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

#include <map>
#include <ostream>
#include <iostream>
#include "HttpHeaders.hpp"

void	HttpHeaders::print(std::ostream &os) const
{

        std::map<std::string, std::string>::const_iterator it;

        for (it = this->map::begin(); it != this->map::end(); ++it)
        {
                os << it->first << ": " << it->second << std::endl;
        }
}
