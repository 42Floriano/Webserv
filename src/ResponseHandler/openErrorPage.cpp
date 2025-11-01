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

#include <fcntl.h>
#include "ConfigIter.hpp"
#include "ResponseHandler.hpp"

template<typename T>
static std::string to_string(T t)
{
        std::stringstream ss;
        ss << t;
        return ss.str();
}

int	ResponseHandler::openErrorPage(int status_code, ssize_t	*len)
{
        // loops over config error pages
        ConfigIter	it = ConfigIter::begin(this->getServerConfig(), "error_page");
        ConfigIter	end = ConfigIter::end(this->getServerConfig());
        for (; it != end; ++it)
        {
                // if error code match
                if (it->args[0] == to_string(status_code))
                {
                        return this->openRegularFile(it->args[1].c_str(), O_RDONLY, len);
                }
        }
        return (-1);
}
