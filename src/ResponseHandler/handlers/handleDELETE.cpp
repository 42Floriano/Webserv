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

void ResponseHandler::handleDELETE(void)
{
        std::string decodedFullPath = Url::decode(this->resolvedRequestPath());
        std::string decodedPath = Url::decode(this->req.path());

        if (decodedPath.find("..") != std::string::npos)
                return handleError(400);

        struct stat st;
        if (stat(decodedFullPath.c_str(), &st))
                return handleError(404);
        if (!S_ISREG(st.st_mode) || access(decodedFullPath.c_str(), W_OK))
                return handleError(403);
        if (std::remove(decodedFullPath.c_str()) != 0)
        {
                if (errno == EACCES || errno == EPERM)
                        return handleError(403);
                else
                        return handleError(500);
        }
        this->setStatusLine(200);
        this->setContentLength(0);
        this->sealHeaders();
}

