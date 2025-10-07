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

bool	ResponseHandler::isCGI(void)
{

        ConfigItem &loc = this->getLocation();
        try
        {
                const std::string cgi_ext = loc.getField("cgi_extension").args[0];
                console::debug << "Found CGI extension rule" << std::endl;
                return true;
        }
        catch (const std::exception &err)
        {
                console::debug << "CGI extension rule not found" << std::endl;
                return false;
        }
}
