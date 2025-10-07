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

Request::Request(std::stringbuf &s): HttpMessage(s)
{
        this->url = NULL;
        this->query = NULL;
}

Request::~Request(void)
{
        if (this->url)
                delete this->url;
        if (this->query)
                delete this->query;
}
