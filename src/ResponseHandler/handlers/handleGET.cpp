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

#include "ResponseHandler.hpp"
#include <fcntl.h>

void	ResponseHandler::handleGET(void)
{
        std::string	filepath = this->resolvedRequestPath();
        ssize_t len;
        int	fd = this->openRegularFile(filepath, O_RDONLY, &len);

        if (fd > -1 && len > -1)
        {
                this->setStatusLine(200);
                this->setContentType(filepath);
                this->setContentLength(len);
                this->sealHeaders();

                this->internal_handler = new FdReader(
                        this->pset,
                        fd,
                        this->res._body.rdbuf()
                );
        }
        else if (fd > -1)
        {
                throw std::runtime_error("We do not handle chunked response");
        }
        else
        {
                this->handleError(-fd);
        }
}
