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
        console::debug << "Opening " << Url::decode(this->getRequestPath()) <<
                          " for GET req" << std::endl;
		std::string	filepath = Url::decode(this->getRequestPath());
        int	fd = this->openReg(filepath, O_RDONLY);

        if (fd > -1)
        {
                size_t len = getFileLength(filepath);

                this->setStatusLine(200);
                this->setContentType(filepath);
                this->setContentLength(len);
                this->sealHeaders();
                this->internal_handler = new FdReader(
                        fd,
                        this->_pset,
                        this->_res._body.rdbuf()
                );
        }
        else
        {
                switch (fd)
                {
                case -1:
                        setErrorResponse("", 500);
                        break;
                case -2:
                        setErrorResponse("", 404);
                        break;
                case -3:
                        setErrorResponse("", 403);
                        break;
                default:
                        setErrorResponse("", 500);
                        break;
                }
        }
}
