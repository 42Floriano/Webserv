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

void    ResponseHandler::setErrorResponse(const std::string &msg,
                int statusCode)
{
        (void) msg;
        size_t len = 0;
        this->setStatusLine(statusCode);
        int fd = this->getErrorPageFd(statusCode, &len);
        this->setContentLength(len);
        this->sealHeaders();
        if (fd != -1)
        {
                this->internal_handler = new FdReader(
                        fd,
                        this->_pset,
                        this->_res._body.rdbuf()
                );
        }
}
