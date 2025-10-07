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

bool	ResponseHandler::isRedirection(void)
{
        ConfigItem &loc = this->getLocation();
        try
        {
                const int return_num = atoi(loc.getField("return").args[0].c_str());
                const std::string return_path = loc.getField("return").args[1];
                console::debug << "Found return field: " << return_num <<  " " << return_path <<
                               std::endl;
                return true;
        }
        catch (const std::exception &e)
        {
                console::debug << "return field not found" << std::endl;
                return false;
        }
}
