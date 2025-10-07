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

#include "Response.hpp"

//TODO: nbr_tostr already defined in resolve_path.cpp, we must put it
// elsewhere as non-static func.

template<typename Number>
static std::string	nbr_tostr(Number n)
{
        std::stringstream	str;

        str << n;
        return str.str();
}

void Response::setErrorResponse(const std::string &message)
{

        this->_body << "<html><body><h1>Error " + _first_line[1] + "</h1><p>" + message
                    + "</p></body></html>";
}
