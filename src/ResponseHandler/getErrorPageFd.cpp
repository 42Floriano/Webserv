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

int	ResponseHandler::getErrorPageFd(int status_code, size_t	*len)
{
        try
        {
                std::stringstream ss;
                ss << status_code;
                ConfigIter	it = ConfigIter::begin(this->getServerConfig(), "error_page");
                ConfigIter	end = ConfigIter::end(this->getServerConfig());

                for (; it != end; ++it)
                {
                        if (it->args[0] == ss.str())
                        {
                                int fd = open(it->args[1].c_str(), O_RDONLY);
                                if (fd == -1)
                                        console::error << "Failed to open error page at " << it->args[1] << std::endl;
                                else
                                {
                                        *len = getFileLength(it->args[1].c_str());
                                        return fd;
                                }
                        }
                }
                *len = 0;
                return (-1);
        }
        catch (const std::exception &err)
        {
                console::error << err.what() << std::endl;
                return -1;

        }
}
