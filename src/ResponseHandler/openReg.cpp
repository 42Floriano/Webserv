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

int     ResponseHandler::openReg(std::string path, int bit)
{
        struct stat st;

        if(stat(path.c_str(), &st) != 0)
        {
                console::error << "stat error" << std::endl;
                return -2;
        }

        if(!S_ISREG(st.st_mode))
        {
                console::error << "Path is not a regular file" << std::endl;
                return -3;
        }

        if(access(path.c_str(), R_OK))
        {
                console::error << "File is not readable" << std::endl;
                return -3;
        }

        console::debug << "Path is a file - FD returned" << std::endl;

        int fd = open(path.c_str(), bit);

        if(fd < 0)
                console::error << "Failed to open file" << std::endl;

        return fd;
}
