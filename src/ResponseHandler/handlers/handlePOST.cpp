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

void	ResponseHandler::handlePOST(void)
{
        if (this->_req._headers.content_length() == -1)
        {
                this->setErrorResponse("", 411);
                return;
        }
        if (this->_req._headers.content_length() > this->getMaxBodySize())
        {
                this->setErrorResponse("", 413);
                return;
        }
        std::string filename = getFilename();

        console::info << "POST: url-decoding " << filename << std::endl;
        console::info << "POST: opening " << Url::decode(filename) << std::endl;

        errno = 0;
        int fd = open(
                         Url::decode(filename).c_str(),
                         O_WRONLY | O_CREAT |O_TRUNC,
                         0644
                 );

        if (fd != -1 && errno == 0)
        {
                this->internal_handler = new FdWriter(
                        fd,
                        this->_pset,
                        this->_req._body.rdbuf()
                );
                this->setStatusLine(200);
                this->setContentLength(0);
                this->sealHeaders();
        }
        else
        {
                console::error << "Open error while handling POST request: " << strerror(
                                       errno) << std::endl;
                this->setErrorResponse("", 409);
        }
}
