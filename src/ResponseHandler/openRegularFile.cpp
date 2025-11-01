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

int     ResponseHandler::openRegularFile(std::string path, int flags,
                ssize_t *filesize)
{
        console::debug << "Checking if path is a regular file" << std::endl;
        struct stat st;

        if(stat(path.c_str(), &st) != 0)
        {
                console::error << "stat error" << std::endl;
                return -404;
        }

        if(!S_ISREG(st.st_mode))
        {
                console::error << "Path is not a regular file" << std::endl;
                return -403;
        }

        if(access(path.c_str(), R_OK))
        {
                console::error << "File is not readable" << std::endl;
                return -403;
        }
        console::debug << "It is!" << std::endl;

        errno = 0;
        int fd = open(path.c_str(), flags);
        const char *errormsg = strerror(errno);

        if(fd < 0)
        {
                console::error << "Failed to open file: " << errormsg << std::endl;
                return -500;

        }

        if (filesize != NULL)
        {
                try
                {
                        *filesize = this->getFileLength(path);
                }
                catch (const std::exception &err)
                {
                        *filesize = -1;
                }
        }

        return fd;
}
