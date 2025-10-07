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

std::string	ResponseHandler::getFilename(void)
{
        const ConfigItem	&location = this->getLocation();
        const ConfigItem	*header = location["upload_filename_header"];
        std::string	filename;

        if (header)
        {
                const std::string &header_name = header->args[0];
                const std::string *filename_ptr = this->_req._headers.get(header_name);
                if (filename_ptr)
                {
                        filename = *filename_ptr;
                        filename = location["root"]->args[0] + location.args[0] + filename;
                }
        }
        if (filename.empty())
        {
                filename = this->getRequestPath();
        }
        return filename;
}
