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

ssize_t ResponseHandler::getMaxBodySize(void) const
{
        try
        {
                ssize_t		retval = -1;
                ConfigItem	&server = this->getServerConfig();

                if (server["max_body_size"])
                {
                        std::stringstream ss(server["max_body_size"]->args[0]);
                        ss >> retval;
                }
                return retval;
        }
        catch (const std::exception &err)
        {
                console::error << err.what() << std::endl;
                return (-1);
        }
}
