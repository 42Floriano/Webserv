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

#include "FdReader.hpp"
#include "ResponseHandler.hpp"

void    ResponseHandler::handleError(int statusCode)
{
        ssize_t len = 0;
        this->setStatusLine(statusCode);

        int fd;
        try
        {
                fd = this->openErrorPage(statusCode, &len);
        }
        catch (const std::exception &err)
        {
                console::error << "On error " << statusCode
                               << ", could not open error page: " << err.what() << std::endl;
                this->setContentLength(0);
                this->sealHeaders();
                return;
        }

        if (fd > -1 && len > -1)
        {
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
                this->setContentLength(0);
                this->sealHeaders();
        }
}
