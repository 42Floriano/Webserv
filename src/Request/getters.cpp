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
#include <string>
#include <iostream>
#include "../QueryString/QueryString.hpp"
#include "../Url/Url.hpp"
#include "Request.hpp"

const std::string&	Request::method(void) const
{
        return (_first_line[0]);
}

const std::string&	Request::path(void) const
{
        return (_first_line[1]);
}

const std::string&	Request::request_version(void) const
{
        return (_first_line[2]);
}
